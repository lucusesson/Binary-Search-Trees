#include "bst.h"
#include "assert.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"



// Name: Lucus Esson
// login ID: lbesson

const int PRE_ORDER = 0;
const int IN_ORDER = 1;
const int POST_ORDER = 2;


struct bstnode *new_leaf(int i) {
  struct bstnode *leaf = malloc(sizeof(struct bstnode));
  leaf->item = i;
  leaf->left = NULL;
  leaf->right = NULL;
  leaf->size = 1;
  return leaf;
}

// bst_create() returns a pointer to a new (empty) bst
// effects: allocates memory (caller must call bst_destroy)
// time: O(1)
struct bst *bst_create(void) {
  struct bst *tree = malloc(sizeof(struct bst));
  tree->root = NULL;
  return tree;
}

static void free_nodes(struct bstnode *node) {
  if(node) {
    free_nodes(node->left);
    free_nodes(node->right);
    free(node);
  }
}


void bst_destroy(struct bst *t) {
  assert(t);
  free_nodes(t->root);
  free(t);
}

// bst_size(t) returns the number of nodes in the bst
// time: O(1)
int bst_size(struct bst *t) {
  if(t->root == NULL) {
    return 0;
  }
  return t->root->size;
}

// bst_insert(i, t) inserts the item i into the bst t
// effects: modifies t if i is not already in t
// time: O(h)
static struct bstnode *insert_node(int i, struct bstnode *node) {
  if(node == NULL) {
    node = new_leaf(i);
  }
  else if(i < node->item) {
    node->size++;
    node->left = insert_node(i, node->left);
  }
  else if(i > node->item) {
    node->size++;
    node->right = insert_node(i, node->right);
  }
  return node;
}


void bst_insert(int i, struct bst *t) {
  assert(t);
  if(bst_find(i,t)) return;
  t->root = insert_node(i, t->root);
}


// bst_find(i, t) determines if i is in t
// time: O(h) where h is the height of the tree
bool bst_find(int i, struct bst *t) {
  assert(t);
  struct bstnode *curnode = t->root;
  while(curnode) {
    if(i == curnode->item) {
      return true;
    }
    else if(i < curnode->item) {
      curnode = curnode->left;
    }
    else {
      curnode = curnode->right;
    }
  }
  return false;
}

// bst_select(k, t) returns the k'th element from t in sorted order
// requires: 0 <= k < bst_size(t)
// time: O(h)
int select_node(int k, struct bstnode *node) {
  assert(node && k >= 0 && k < node->size);
  int leftsize = 0;
  if(node->left) leftsize = node->left->size;
  if(k < leftsize) return select_node(k, node->left);
  if(k == leftsize) return node->item;
  return select_node(k - leftsize - 1, node->right);
}

int bst_select(int k, struct bst *t) {
  assert(t);
  assert(t->root);
  return select_node(k, t->root);
}

// bst_remove(i, t) removes i from bst t if it exists
// effects: modifies t if i is in t
// time: O(h)
struct bstnode *node_remove(int i, struct bstnode *node) {
  if(node == NULL) return NULL;
  if(i < node->item) {
    node->size--;
    node->left = node_remove(i, node->left);
  }
  else if(i > node->item) {
    node->size--;
    node->right = node_remove(i, node->right);
  }
  else if(node->left == NULL && node->right == NULL) {
    free(node);
    return NULL;
  }
  else if(node->left == NULL) {
    struct bstnode *backup = node->right;
    free(node);
    return backup;
  }
  else if(node->right == NULL) {
    struct bstnode *backup = node->right;
    free(node);
    return backup;
  }
  else {
    struct bstnode *next = node->right;
    while(next->left) {
      next = next->left;
    }
    node->item = next->item;
    node->right = node_remove(node->item, node->right);
  }
  return node;
}
  
  

void bst_remove (int i, struct bst *t) {
  assert(t);
  if(bst_find(i,t)) {
    t->root = node_remove(i, t->root);
  }
}

// bst_range(start, end, t) returns the number of items in t that are 
//   between the values of start and end (inclusive)
// time: O(n)
int node_range(int start, int end, struct bstnode *node) {
  if(!node) return 0;
  if(node->item == start & node->item == end) return 1;
  if(node->item <= end && node->item >= start) {
    return 1 + node_range(start, end, node->left) +
               node_range(start, end, node->right);
  }
  else if(node->item <= start) {
    return node_range(start, end, node->right);
  }
  else {
    return node_range(start, end, node->left);
  }      
}

int bst_range (int start, int end, struct bst *t) {
  assert(t);
  if(start > end) {
    return node_range(end, start, t->root);
  }
  return node_range(start, end, t->root);
}

// bst_print(o, t) prints the bst to the screen in order o
// example: given a bst with the following structure
//             4
//           /   \
//          2     5
//         / \
//        1   3
//   pre-order print: "[4,2,1,3,5]\n"
//   in-order print: "[1,2,3,4,5]\n"
//   post-order print: "[1,3,2,5,4]\n"
//   if the t is empty, prints "[empty]\n"
// requires: o is a valid order
// effects: displays output
// time: O(n)
static void pre_order(struct bstnode *node) {
  if(node) {
    printf(",%d", node->item);
    pre_order(node->left);
    pre_order(node->right);
  }
}

static void in_order(int l, struct bstnode *node) {
  if(node) {
    in_order(l, node->left);
    if(node->item == l) {
      printf("%d]\n", node->item);
      return;
    }
    printf("%d,", node->item);
    in_order(l, node->right);
  }
}

static void post_order(int end, struct bstnode *node) {
  if(node) {
    post_order(end, node->left);
    post_order(end, node->right);
    if(node->item == end) {
      printf("%d]\n", node->item);
      return;
    }
    printf("%d,", node->item);
  }
}
    
void bst_print(int o, struct bst *t) {
  assert(t);
  assert(o >= PRE_ORDER && o <= POST_ORDER);
  if(t->root == NULL) {
    printf("[empty]\n");
    return;
  }
  if(o == PRE_ORDER) {
    printf("[%d", t->root->item);
    pre_order(t->root->left);
    pre_order(t->root->right);
    printf("]\n");
    return;
  }
  if(o == IN_ORDER) {
    struct bstnode *node = t->root;
    while(node->right) {
      node = node->right;
    }
    int largest = node->item;
    printf("[");
    in_order(largest, t->root);
  }
  if(o == POST_ORDER) {
    struct bstnode *node = t->root;
    int end = node->item;
    printf("[");
    post_order(end, node);
  }
}
    
    

// bst_to_sorted_array(t) returns a pointer to a new array
//   which contains all of the items from t in sorted order
//   returns NULL if t is empty
// effects : allocates memory (caller must free)
// time: O(n)
void node_array(int i, int *a, struct bstnode *node) {
  if(!node) return;
  if(node->left) {
    struct bstnode *next = node->left;
    if(next->right) {
      node_array(i - 1 - next->right->size, a, next);
      //a[i] = node->item;
    }
    else {
      node_array(i - 1, a, next);
      //a[i] = node->item;
    }
  }
  if(node->right) {
    struct bstnode *next = node->right;
    if(next->left) {
      node_array(i + 1 + next->left->size, a, next);
    }
    else {
      node_array(i+1, a, next);
    }
  }
  a[i] = node->item;
}
      

int *bst_to_sorted_array(struct bst *t) {
  assert(t);
  if(t->root == NULL) {
    return NULL;
  }
  int *a = malloc(t->root->size * sizeof(int));
  struct bstnode *node = t->root;
  if(node->right) {
    node_array(node->size - node->right->size - 1, a, node);
    return a;
  }
  else {
    node_array(node->size - 1, a, node);
    return a;
  }
}

// sorted_array_to_bst(a, len) creates a new BALANCED bst that 
//   contains all of the items from a 
// note: the definition of a balanced binary tree is that, for every node 
//   in the tree, the heights of the left and right sub trees differ by 
//   at most 1
// requires: a is sorted in ascending order, len >= 1
// time: O(nlogn), or O(n) for bonus marks
static void array_tree(struct bst *t, int *a, int start, int end) {
  if(start > end) {
    return;
  }
  int mid = (start + end) / 2;
  bst_insert(a[mid], t);
  array_tree(t, a, start, mid-1);
  array_tree(t, a, mid+1, end);
}

struct bst *sorted_array_to_bst(int *a, int len) {
  assert(len);
  struct bst *t = bst_create();
  array_tree(t, a, 0, len -1);
  return t;
}

// bst_rebalance(t) changes t so that it contains all of the same items,
//   but the tree is balanced
// effects: modifies t
// time: O(nlogn)
static void free_nodes2(struct bstnode *node) {
  if(node) {
    free_nodes2(node->left);
    free_nodes2(node->right);
    free(node);
  }
}


void bst_destroy2(struct bst *t) {
  assert(t);
  free_nodes2(t->root);
  t->root = NULL;
}

static void array_tree2(struct bstnode *node, int 
                                   *a, int start, int end) {
  if(start > end) {
    return;
  }
  int mid = (start + end) / 2;
  insert_node(a[mid], node);
  array_tree2(node, a, start, mid-1);
  array_tree2(node, a, mid+1, end);
}

static struct bstnode *sorted_array_to_bst2(int *a, int len) {
  int mid = len/2;
  struct bstnode *root = new_leaf(a[mid]);
  array_tree2(root, a, 0, mid-1);
  array_tree2(root, a, mid+1, len-1);
  return root;
}


void bst_rebalance(struct bst *t) {
  if(t->root == NULL) return;
  int len = t->root->size;
  int *a = bst_to_sorted_array(t);
  bst_destroy2(t);
  t->root = sorted_array_to_bst2(a, len);
  free(a);
}
  
