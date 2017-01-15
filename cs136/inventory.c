#include "inventory.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// INTEGRITY STATEMENT (modify if necessary)
// I received help from the following sources:
// None. I am the sole author of this work 

// sign this statement by removing the line below and entering your name

// Name: Lucus Esson
// login ID: lbesson


struct inventory {
  char **items;
  int *qty;
  int len;
  int maxlen;
};

// inventory_create() returns a new empty inventory
// effects: allocates memory (caller must call inventory_destroy)
// time: O(1)
struct inventory *inventory_create(void){
  struct inventory *inv = malloc(sizeof(struct inventory));
  inv->items = malloc(8 * 32);
  inv->qty = malloc (sizeof(int) * 32);
  inv->len = 0;
  inv->maxlen = 32;
  return inv;
}

// inventory_destroy(inv) frees all dynamically allocated memory 
// effects: the memory at inv is invalid (freed)
// time : O(n)
void inventory_destroy(struct inventory *inv){
  assert(inv);
  for (int i = 0; i < inv->len; i++) {
    free(inv->items[i]);
  }
    free(inv->items);
    free(inv->qty);
    free(inv);
  
}

// inventory_lookup(inv, item) determines the quantity of items in inv
//   returns -1 if item is not in the inventory
//   note: an item with quantity 0 returns 0 (not -1)
// time: O(mlogn)
int inventory_lookup(const struct inventory *inv, const char *item){
  assert(inv);
  int i=0;
  while(i < inv->len){
    if (strcmp(inv->items[i], item) == 0){
      break;
    }
    i++;
  }
  if (i == inv->len) return -1;
  return inv->qty[i];
}

// inventory_add(inv, item, qty) adds qty items to inv
// requires: qty >= 0
// inserts copy of item
// effects: inv is modified
// time: O(mlogn) if item is already in the inventory
//       O(mn) if item does not exist in the inventory
void inventory_add(struct inventory *inv, const char *item, int qty){
  assert(inv);
  if (inv->len == inv->maxlen){
    inv->maxlen *= 2;
    inv->qty = realloc(inv->qty, inv->maxlen * sizeof(int));
    inv->items = realloc(inv->items,inv->maxlen * 8);
  }

  int i = 0;
  while(i < inv->len){
    if (strcmp(inv->items[i], item) == 0){
      break;
    }
    i++;
  }

  if (i == inv->len) {
    char *newstr = malloc(strlen(item)+1);
    strcpy(newstr,item);
    inv->items[inv->len] = newstr;
    inv->qty[inv->len] = qty;
    inv->len++;
  } else {
    inv->qty[i] += qty;
  }
}



// inventory_remove(inv, item, qty) removes qty items from inv
// requires: 0 < qty <= inventory_lookup(inv, item)
// effects: inv is modified
// time: O(mlogn)
void inventory_remove(struct inventory *inv, const char *item, int qty) {
  for(int i = 0; i < inv->len; ++i) {
    if(strcmp(inv->items[i], item) == 0) {
      assert(0 < qty <= inventory_lookup(inv, item));
      inv->qty[i] -= qty;
      break;
    }
  }
}
