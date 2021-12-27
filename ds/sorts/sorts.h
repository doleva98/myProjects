#ifndef __SORT_H__
#define __SORT_H__

#include <stddef.h>

/* DIfferent from the the common_type.h */
typedef int (*cmp_func_t)(const void *curr_data, const void *new_element);

extern void QuickSort(void *base, size_t nmemb, size_t size, cmp_func_t compare);

extern void MergeSort(void *base, size_t nmemb, size_t size, cmp_func_t compare);

extern void *IterBinarySearch(void *base, size_t nmemb, size_t size, cmp_func_t compare, const void *data);

extern void *RecBinarySearch(void *base, size_t nmemb, size_t size, cmp_func_t compare, const void *data);

#endif