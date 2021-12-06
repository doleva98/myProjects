#ifndef _LINEAR_SORTSH_
#define _LINEAR_SORTSH_

#include <stdlib.h>
extern int *CountingSort(int *arr, size_t n);
extern int *RadixSort(int *arr, size_t n);
int *NewRadixSort(int *arr, size_t n, size_t bit_number);

#endif
