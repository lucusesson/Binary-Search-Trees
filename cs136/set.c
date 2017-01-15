#include "mergesort.h"
#include "set.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


// Name: Lucus Esson
// login ID: lbesson

struct set {
  int *a;
  int len;
};
  

// NOTE: All of the following functions REQUIRE:
//       pointers to a set (e.g., s) are valid (not NULL)

// set_create() returns a new empty set
// effects : allocates memory (caller must call set_destroy)
// time: O(1)
struct set *set_create(void) {
  struct set *s = malloc(sizeof(struct set));
  s->a = NULL;
  s->len = 0;
  return s;
}

// set_destroy(s) frees all dynamically allocated memory 
// effects: the memory at s is invalid (freed)
// time: O(1)
void set_destroy(struct set *s) {
  assert(s);
  free(s->a);
  free(s);
}

// set_size(s) returns the number of elements in s
// time: O(1)
int set_size(const struct set *s) {
  return s->len;
}

// set_member(s, i) determines if i is in set s
// time: O(logn)
bool set_member(const struct set *s, int i) {
  assert(s);
  int t = 0; // 0 false, 1 true
  int low = 0;
  int high = s->len-1;
  while(low <= high) {
    int mid = low + (high - low) / 2;
    if (s->a[mid] == i) {
      t =1;
      break;
    } else if (s->a[mid] < i) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }
  if (t == 1) {
    return true;
  }
  else {
    return false;
  }
}
      
    

// set_add(s, i) adds i to the set s, if it does not already contain i
// effects: s may be modified
// time: O(n) where n is set_size(s)
void set_add(struct set *s, int i) {
  assert(s);
  int *b = malloc(s->len + 1 * sizeof(int));
  int ia = 0; //index in a
  int j = 0; //index in b
  while(1) {
    if(ia == s->len) {
      b[j] = i;
      ++s->len;
      free(s->a);
      s->a = b;
      return;
    }
    else if(i > s->a[ia]) {
      b[j] = s->a[ia];
      ++j;
      ++ia;
    }
    else {
      if(i == s->a[ia]) {
        b = realloc(b, s->len * sizeof(int));
        break;
      }
      else {
        ++s->len;
        b[j] = i;
        ++j;
      }
    }
  }
  
 while(ia < s->len) {
   b[j] = s->a[ia];
   ++ia;
   ++j;
 }
  free(s->a);
  s->a = b;
}
  
        
      
    
  

// set_remove(s, i) removes i from s.  if i is not in s, s isn't changed
// effects: s may be modified
// time: O(n) where n is set_size(s)
void set_remove(struct set *s, int i) {
  assert(s);
  int f = 0;
  int *b = malloc(s->len * sizeof(int));
  int j = 0; // index in b
  int ia = 0; // index in a;
  while(1) {
    if(ia == s->len) {
      break;
    }
    else if (i == s->a[ia]) {
      f = 1;
      ++ia;
    }
    else {
      b[j] = s->a[ia];
      ++j;
      ++ia;
    }
  }
  if (f == 1) {
    b = realloc(b, ((s->len) - 1) * sizeof(int));
    s->len--;
    free(s->a);
    s->a = b;
  }
  else {
    s->len--;
    free(s->a);
    s->a = b;
  }
}
    

// set_union(s1, s2) returns a new set that is the union of s1 and s2
// effects: allocates memory for the new set (caller must call set_destroy)
// time: O(n) where n is set_size(s1) + set_size(s2)
struct set *set_union(const struct set *s1, const struct set *s2) {
  assert(s1 && s2);
  struct set *s = malloc(sizeof(struct set));
  int *b = malloc((s1->len + s2->len) * sizeof(int));
  int s1_i = 0; //index of s1
  int s2_i = 0; //index of s2
  int b_i = 0; //index of b
  while(1) {
    if(s1_i == s1->len) {
      while(s2_i != s2->len) {
        b[b_i] = s2->a[s2_i];
        b_i++;
        s2_i++;
      }
      break;
    }
    else if(s2_i == s2->len) {
      while(s1_i != s1->len) {
        b[b_i] = s1->a[s1_i];
        b_i++;
        s1_i++;
      }
      break;
    }
    else {
      if(s2->a[s2_i] == s1->a[s1_i]) {
        b[b_i] = s2->a[s2_i];
        ++b_i;;
        ++s2_i;;
        ++s1_i;;
      }
      else if(s2->a[s2_i] < s1->a[s1_i]) {
        b[b_i] = s2->a[s2_i];
        ++b_i;
        ++s2_i;
      }
      else {
        b[b_i] = s1->a[s1_i];
        ++b_i;
        ++s1_i;
      }
    }
  }
  b = realloc(b, b_i *sizeof(int));
  s->len = b_i;
  s->a = b;
  return s;
}
        
      
    

// set_intersect(s1, s2) returns a new set that is the intersection of s1 and s2
// effects: allocates memory for the new set (caller must call set_destroy)
// time: O(n) where n is set_size(s1) + set_size(s2)
struct set *set_intersect(const struct set *s1, const struct set *s2) {
  assert(s1 && s2);
  struct set *s = malloc(sizeof(struct set));
  int *b = malloc((s1->len + s2->len) * sizeof(int));
  int s1_i = 0; //index of s1
  int s2_i = 0; //index of s2
  int b_i = 0; //index of b
  while(1) {
    if(s1_i == s1->len || s2_i == s2->len) {
      break;
    }
    else if(s1->a[s1_i] == s2->a[s2_i]) {
      b[b_i] = s1->a[s1_i];
      ++b_i;
      ++s1_i;
      ++s2_i;
    }
    else if(s1->a[s1_i] < s2->a[s2_i]) {
      ++s1_i;
    }
    else {
      ++s2_i;
    }
  }
  b = realloc(b, b_i * sizeof(int));
  s->len = b_i;
  s->a = b; 
  return s;
}
    
  

// array_to_set(a, len) returns a new set that is all the unique elements of a
// requires: len > 0
// effects: allocates memory for the new set (caller must call set_destroy)
// time: O(nlogn)
struct set *array_to_set(const int a[], int len) {
  assert(len>0);
  struct set *s = malloc(sizeof(struct set));
  int *b = malloc(len * sizeof(int));
  for(int i = 0; i < len; ++i) {
    b[i] = a[i];
  }
  merge_sort(b,len);
  int *c = malloc(len * sizeof(int));
  int ci = 0; // index of c
  c[0] = b[0];
  for(int i = 1; i < len; ++i) {
    if(c[ci] == b[i]) {
    }
    else {
      ++ci;
      c[ci] = b[i];
    }
  }
  ++ci;
  free(b);
  c = realloc(c, ci * sizeof(int));
  s->len = ci ;
  s->a = c;
  return s;
}
    
    

// set_to_array(s) returns a new array that is the elements of s
//   in ascending order, or NULL if s is empty
// effects: may allocate memory for a new array (caller must call free)
// time: O(n)
int *set_to_array(const struct set *s) {
  assert(s);
  if(s->a == NULL) {
    return NULL;
  }
  int *b = malloc(s->len * sizeof(int));
  int ai = 0; //index of s->a
  int bi = 0; //index of b
  while(ai < s->len) {
    b[bi] = s->a[ai];
    ++ai;
    ++bi;
  }
  return b;
}

// set_print(s) prints the elements of set s to the screen in ascending order.
//   using the format: "[element_smallest,element_next,...,element_largest]\n"
//   or "[empty]\n"
// effects: prints out a message
// time: O(n)
void set_print(const struct set *s) {
  assert(s);
  if(s->a == NULL) {
    printf("[empty]\n");
  }
  else {
    printf("[");
    for(int i = 0; i < s->len; ++i) {
      if(i == s->len-1) {
        printf("%d]\n", s->a[i]);
      }
      else {
        printf("%d,", s->a[i]);
      }
    }
  }
}
