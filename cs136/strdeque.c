#include "strdeque.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"


// Name: Lucus Esson
// login ID: lbesson

struct llnode {
  char *s;
  struct llnode *next;
  struct llnode *prev;
};

struct strdeque {
  struct llnode *front;
  struct llnode *back;
  int len;
};

// strdeque_create() returns a pointer to a new (empty) strdeque
// effects: allocates memory (caller must call strdeque_destroy)
// time: O(1)
struct strdeque *strdeque_create(void) {
  struct strdeque *s = malloc(sizeof(struct strdeque));
  s->front = NULL;
  s->back = NULL;
  s->len = 0;
  return s;
}

// strdeque_destroy(sdeq) frees all dynamically allocated memory 
// effects: the memory at sd is invalid (freed)
// time: O(n)
void strdeque_destroy(struct strdeque *sdeq) {
  assert(sdeq);
  struct llnode *node = sdeq->front;
  for(int i = 0; i < sdeq->len; ++i) {
    free(node->s);
    free(node);
    node = node->next;
  }
  free(sdeq);
}
    

// strdeque_is_empty(sdeq) determines if sdeq is empty
// time: O(1)
bool strdeque_is_empty(const struct strdeque *sdeq) {
  assert(sdeq);
  if(sdeq->len == 0) {
    return true;
  }
  else {
    return false;
  }
}

// strdeque_add_front(str, sdeq) adds str to the front of sdeq
// note: makes a copy of str
// effects: modifies sdeq
// time: O(m), where m is the length of str
void strdeque_add_front(const char *str, struct strdeque *sdeq) {
  assert(sdeq);
  assert(str);
  char *newstring = malloc(strlen(str)+1);
  strcpy(newstring,str);
  struct llnode *node = malloc(sizeof(struct llnode));
  node->s = newstring;
  if(sdeq->front == NULL) {
    sdeq->front = node;
    sdeq->back = node;
    node->next = NULL;
    node->prev = NULL;
    sdeq->len++;
    return;
  }
  struct llnode *backup = sdeq->front;
  sdeq->front = node;
  node->next = backup;
  backup->prev = node;
  node->prev = NULL;
  sdeq->len++;
}
  

// strdeque_add_back(str, sdeq) adds str to the back of sdeq
// note: makes a copy of str
// effects: modifies sdeq
// time: O(m), where m is the length of str
void strdeque_add_back(const char *str, struct strdeque *sdeq) {
  assert(sdeq);
  assert(str);
  char *newstring = malloc(strlen(str)+1);
  strcpy(newstring,str);
  struct llnode *node = malloc(sizeof(struct llnode));
  node->s = newstring;
  if(sdeq->len == 0) {
    sdeq->front = node;
    sdeq->back = node;
    node->next = NULL;
    node->prev = NULL;
    sdeq->len++;
    return;
  }
  struct llnode *backup = sdeq->back;
  sdeq->back->next = node;
  sdeq->back = node;
  node->next = NULL;
  node->prev = backup;
  sdeq->len++;
}

// strdeque_remove_front(sdeq) removes front of sdeq
// requires: sdeq is not empty
// effects: modifies sdeq
// time: O(1)
void strdeque_remove_front(struct strdeque *sdeq) {
  assert(sdeq);
  assert(sdeq->front);
  if(sdeq->front->next == NULL) {
    free(sdeq->front->s);
    free(sdeq->front);
    sdeq->front = NULL;
    sdeq->back = NULL;
    sdeq->len = 0;
    return;
  }
  struct llnode *backup = sdeq->front->next;
  free(sdeq->front->s);
  free(sdeq->front);
  backup->prev = NULL;
  sdeq->front = backup;
  sdeq->len--;
}

// strdeque_remove_front(sdeq) removes back of sdeq
// requires: sdeq is not empty
// effects: modifies sdeq
// time: O(1)
void strdeque_remove_back(struct strdeque *sdeq) {
  assert(sdeq);
  assert(sdeq->front);
  if(sdeq->front->next == NULL) {
    free(sdeq->front->s);
    free(sdeq->front);
    sdeq->front = NULL;
    sdeq->back = NULL;
    sdeq->len = 0;
    return;
  }
  struct llnode *backup = sdeq->back->prev;
  free(sdeq->back->s);
  free(sdeq->back);
  backup->next = NULL;
  sdeq->back = backup;
  sdeq->len--;
}
  

// strdeque_front(sdeq) returns the string at the front of sdeq
// requires: sdeq is not empty
// time: O(1)
const char *strdeque_front(const struct strdeque *sdeq) {
  assert(sdeq);
  assert(sdeq->front);
  return sdeq->front->s;
}

// strdeque_back(sdeq) returns the string at the front of sdeq
// requires: sdeq is not empty
// time: O(1)
const char *strdeque_back(const struct strdeque *sdeq) {
  assert(sdeq);
  assert(sdeq->front);
  return sdeq->back->s;
}
