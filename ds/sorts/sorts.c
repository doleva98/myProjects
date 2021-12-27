#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "sorts.h"

static void *MergeSortHelper(void *base, size_t size, cmp_func_t compare, size_t l, size_t r);
static void *Merge(void *base, size_t size, cmp_func_t compare, size_t l, size_t m, size_t r);

void MergeSort(void *base, size_t nmemb, size_t size, cmp_func_t compare)
{
	assert(base);
	MergeSortHelper(base, size, compare, 0, nmemb - 1);
}

void QuickSort(void *base, size_t nmemb, size_t size, cmp_func_t compare);

void *IterBinarySearch(void *base, size_t nmemb, size_t size, cmp_func_t compare, const void *data);

void *RecBinarySearch(void *base, size_t nmemb, size_t size, cmp_func_t compare, const void *data);

static void *MergeSortHelper(void *base, size_t size, cmp_func_t compare, size_t l, size_t r)
{
	size_t m = 0;
	if (r <= l)
	{
		return NULL;
	}
	m = l + (r - l) / 2;

	MergeSortHelper(base, size, compare, l, m);
	MergeSortHelper(base, size, compare, m + 1, r);
	return Merge(base, size, compare, l, m, r);
}

static void *Merge(void *base, size_t size, cmp_func_t compare, size_t l, size_t m, size_t r)
{
	size_t i, j, k;
	size_t n1 = m - l + 1;
	size_t n2 = r - m;

	void *left_arr = NULL;
	void *right_arr = NULL;

	left_arr = malloc(size * n1);
	if (!left_arr)
	{
		return NULL;
	}

	memcpy(left_arr, base, size * n1);

	right_arr = malloc(size * n1);
	if (!right_arr)
	{
		return NULL;
	}

	memcpy(right_arr, (char *)base + (size * n1), size * n1);
}