#include "priqueue.h"
#include <assert.h>
#include <stdio.h>



// Name: Lucus Esson
// login ID: lbesson

struct priqueue {
  int *pri;
  int *item;
  int len;
  int max;
};

static void swap(struct priqueue *pq, int i, int j) {
  int save_pri = pq->pri[i];
  int save_item = pq->item[i];
  pq->pri[i] = pq->pri[j];
  pq->item[i] = pq->item[j];
  pq->pri[j] = save_pri;
  pq->item[j] = save_item;
}


// priqueue_create() returns a pointer to a new (empty) priqueue
// effects: allocates memory (caller must call priqueue_destroy)
// time: O(1)
struct priqueue *priqueue_create(void) {
  struct priqueue *p = malloc(sizeof(struct priqueue));
  p->pri = malloc(sizeof(int));
  p->item = malloc(sizeof(int));
  p->len = 0;
  p->max = 1;
  return p;
}

// priqueue_destroy(pq) frees all dynamically allocated memory 
// effects: the memory at pq is invalid (freed)
// time: O(1)
void priqueue_destroy(struct priqueue *pq) {
  assert(pq);
  free(pq->pri);
  free(pq->item);
  free(pq);
}

// priqueue_length(pq) determines how many items are in pq
// time: O(1)
int priqueue_length(const struct priqueue *pq) {
  assert(pq);
  return pq->len;
}

// priqueue_add(pq, item, priority) inserts item with priority into pq
// effects: modifies pq
// time: O(logn)
void priqueue_add(struct priqueue *pq, int item, int priority) {
  assert(pq);
  if(pq->len == pq->max) {
    pq->max *= 2;
    pq->pri = realloc(pq->pri, pq->max * sizeof(int));
    pq->item = realloc(pq->item, pq->max * sizeof(int));
  }
  pq->item[pq->len] = item;
  pq->pri[pq->len] = priority;
  if(pq->len == 0) {
    ++pq->len;
    return;
  }
  int cur = pq->len;
  int p;
  while(cur > 0) {
    if(cur % 2 == 0) {
      p = (cur - 2)/2;
    }
    else {
      p = (cur - 1)/2;
    }
    if(pq->pri[p] < pq->pri[cur]) {
      swap(pq, p, cur);
    }
    else break;
    cur = p;
  }
  ++pq->len;
}


// priqueue_front(pq) returns the item with the highest priority
//   If there are multiple items with the same priority, 
//   the order does not matter.
// requires: pq is not empty
// time : O(1)
int priqueue_front(const struct priqueue *pq) {
  assert(pq);
  assert(pq->len != 0);
  return pq->item[0];
}

// priqueue_remove(pq) removes and returns the item with the maximum 
//   priority in pq.
//   If there are multiple items with the same priority, 
//   the order does not matter.
// requires: pq is not empty
// effects: modifies pq
// time: O(logn)
int priqueue_remove(struct priqueue *pq) {
  assert(pq);
  assert(pq->len != 0);
  int save = pq->item[0];
  if(pq->len == 1) {
    --pq->len;
  }
  else if(pq->len == 2) {
    pq->pri[0] = pq->pri[1];
    pq->item[0] = pq->item[1];
    pq->len--;
  }
  else if(pq->len == 3) {
    pq->pri[0] = pq->pri[2];
    pq->item[0] = pq->item[2];
    pq->len--;
    if(pq->pri[0] < pq->pri[1]) {
      swap(pq, 0, 1);
    }
  }
  else {
    pq->pri[0] = pq->pri[pq->len-1];
    pq->item[0] = pq->item[pq->len-1];
    pq->len--;
    int i = 0;
    while((i*2)+2 < pq->len) {
      if(pq->pri[i] < pq->pri[(i*2)+1] ||
         pq->pri[i] < pq->pri[(i*2)+2]) {
        if(pq->pri[(i*2)+1] > pq->pri[(i*2)+2]) {
          swap(pq, i, (i*2)+1);
          i = (i*2)+1;
        }
        else {
          swap(pq, i, (i*2)+2);
          i = (i*2)+2;
        }

      }
      else {
        break;
      }
    }
  }

  return save;
}




// NOTE: priqueue_print violates the principle of information hiding
//       but is required to properly test your code

// priqueue_print(pq) prints pq
// effects: displays output
// example: It prints in the order it is stored in the array. 
//   For example, if the heap is currently
//             (1,99)
//             /    \
//         (5,20)  (2,30)
//   then it will be printed as "[(1:99),(5:20),(2:30)]\n"
//   where each node is printed as (item:priority).
//   if empty, it prints as "[empty]\n"
// time: O(n)
void priqueue_print(const struct priqueue *pq) {
  assert(pq);
  if(pq->len == 0) {
    printf("[empty]\n");
    return;
  }
  printf("[");
  for(int i = 0; i < pq->len; ++i) {
    printf("(%d:%d)", pq->item[i], pq->pri[i]);
    if(i == pq->len -1) {
      printf("]\n");
      break;
    }
    printf(",");
  }
}
