#include "sequence.h"


// INTEGRITY STATEMENT (modify if necessary)
// I received help from the following sources:
// None. I am the sole author of this work 

// sign this statement by removing the line below and entering your name
// Name: Lucus Esson
// login ID: lbesson

struct llnode {
  int item;
  struct llnode *next;
};

struct sequence {
  struct llnode *front;
  int len;
};


struct sequence *sequence_create(void) {
  struct sequence *s = malloc(sizeof(struct sequence));
  s->front = NULL;
  s->len = 0;
  return s;
}


void sequence_destroy(struct sequence *seq) {
  assert(seq);
  struct llnode *curnode = seq->front;
  while(curnode) {
    struct llnode *next = curnode->next;
    free(curnode);
    curnode = next;
  }
  free(seq);
}


int sequence_length(const struct sequence *seq) {
  assert(seq);
  return seq->len;
}


int sequence_item_at(const struct sequence *seq, int pos) {
  assert(seq);
  assert(0 <= pos && pos < seq->len);
  struct llnode *node = seq->front;
  for(int i = 0; ; ++i) {
    if(i == pos) {
      return node->item;
    }
    node = node->next;
  }
}


void sequence_insert_at(struct sequence *seq, int pos, int val) {
  assert(seq);
  assert(0 <= pos && pos <= seq->len);
  struct llnode *newnode = malloc(sizeof(struct llnode));
  newnode->item = val;
  if(seq->front == NULL) {
    newnode->next = NULL;
    seq->front = newnode;
    seq->len++;
    return;
  }
  if(pos == 0) {
    newnode->next = seq->front;
    seq->front = newnode;
    seq->len++;
    return;
  }
  struct llnode *curnode = seq->front;
  for(int i = 1; curnode->next; ++i) {
    if(pos == i) {
      struct llnode *backup = curnode->next;
      newnode->next = backup;
      curnode->next = newnode;
      seq->len++;
      return;
    }
    curnode = curnode->next;
  }
  curnode->next = newnode;
  newnode->next = NULL;
  seq->len++;
}

int sequence_remove_at(struct sequence *seq, int pos) {
  assert(seq);
  assert(0 <= pos && pos < seq->len);
  if(pos == 0) {
    int retval = seq->front->item;
    struct llnode *backup = seq->front;
    seq->front = seq->front->next;
    free(backup);
    seq->len--;
    return retval;
  }
  struct llnode *curnode = seq->front->next;
  struct llnode *prevnode = seq->front;
  for(int i = 1; ;++i) {
    if(i == pos) {
      prevnode->next = curnode->next;
      int retval = curnode->item;
      free(curnode);
      seq->len--;
      return retval;
    }
    prevnode = curnode;
    curnode = curnode->next;
  }
}

// sequence_print(seq) prints out the items in seq
//   using the format: "[item_0,item_1,...,item_last]\n"
//   or "[empty]\n"
// effects: prints out a message
// time : O(n)
void sequence_print(const struct sequence *seq) {
  assert(seq);
  if(seq->front == NULL) {
    printf("[empty]\n");
    return;
  }
  printf("[");
  struct llnode *node = seq->front;
  for(int i = 0; i < seq->len; ++i) {
    if(i == seq->len - 1) {
      printf("%d]\n", node->item);
    }
    else {
      printf("%d,", node->item);
    }
    node = node->next;
  }
}

