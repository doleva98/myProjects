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
	if (l < r)
	{
		m = l + (r - l) / 2;

		MergeSortHelper(base, size, compare, l, m);
		MergeSortHelper(base, size, compare, m + 1, r);
		Merge(base, size, compare, l, m, r);
	}
	return base;
}

static void *Merge(void *base, size_t size, cmp_func_t compare, size_t l, size_t m, size_t r)
{
	size_t i = 0, j = 0, k = l;
	size_t n1 = m - l + 1;
	size_t n2 = r - m;

	void *left_arr = NULL;
	void *right_arr = NULL;

	left_arr = malloc(size * n1);
	if (!left_arr)
	{
		return NULL;
	}

	memcpy(left_arr, (void *)((size_t)base + (l * size)), size * n1);

	right_arr = malloc(size * n2);
	if (!right_arr)
	{
		free(left_arr);
		return NULL;
	}

	memcpy(right_arr, (void *)((size_t)base + (size * (n1 + l))), size * n2);

	while (i < n1 && j < n2)
	{
		if (compare((void *)((size_t)left_arr + (i * size)), (void *)((size_t)right_arr + (j * size))) < 0)
		{
			memcpy((void *)((size_t)base + (k * size)), (void *)((size_t)left_arr + (i * size)), size);
			++i;
		}
		else
		{
			memcpy((void *)((size_t)base + (k * size)), (void *)((size_t)right_arr + (j * size)), size);
			++j;
		}
		++k;
	}

	while (i < n1)
	{
		memcpy((void *)((size_t)base + (k * size)), (void *)((size_t)left_arr + (i * size)), size);
		++i;
		++k;
	}

	while (j < n2)
	{
		memcpy((void *)((size_t)base + (k * size)), (void *)((size_t)right_arr + (j * size)), size);
		++j;
		++k;
	}
	free(left_arr);
	free(right_arr);
	return base;
}