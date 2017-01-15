#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aos_sort.h"

// INTEGRITY STATEMENT (modify if necessary)
// I received help from the following sources:
// None. I am the sole author of this work 

// sign this statement by removing the line below and entering your name
// Name: Lucus Esson 
// login ID: lbesson

static void aos_merge(char *dest[], char *src1[], int len1,
                  char *src2[], int len2) {
  int pos1 = 0;
  int pos2 = 0;
  for (int i=0; i < len1 + len2; ++i) {
    if (pos1 == len1 || (pos2 < len2 && strcmp(src2[pos2] ,src1[pos1]) < 0)) {
      dest[i] = src2[pos2];
      ++pos2;
    } else {
      dest[i] = src1[pos1];
      ++pos1;
    }
  }
}

void aos_merge_sort(char *a[], const int len) {
  if (len <= 1) return;
  int llen = len / 2;
  int rlen = len - llen;

  char **left = malloc(llen * sizeof(char *));
  char **right = malloc(rlen * sizeof(char *));

  for (int i=0; i < llen; ++i) left[i] = a[i];
  for (int i=0; i < rlen; ++i) right[i] = a[i + llen];  

  aos_merge_sort(left, llen);
  aos_merge_sort(right, rlen);

  aos_merge(a, left, llen, right, rlen);

  free(left);
  free(right);

}
