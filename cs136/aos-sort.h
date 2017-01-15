// SEASHELL_READONLY

// aos_merge_sort(aos, len) sorts the array of strings (aos)
// note: it does not mutate any strings: it sorts the array of pointers
// effects: modifies aos
// time: O(m*n*logn), n is len
//                    m is the length of the longest string in aos
void aos_merge_sort(char *aos[], int len);
