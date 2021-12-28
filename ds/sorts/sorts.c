#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "sorts.h"

static void *Merge(void *base, size_t size, cmp_func_t compare, size_t l, size_t m, size_t r);
static void MergeSortHelper(void *base, size_t size, cmp_func_t compare, size_t l, size_t r);
static void QuickSortHelper(void *base, size_t size, cmp_func_t compare, size_t l, size_t r);
static size_t QuickSortPartition(void *base, size_t size, cmp_func_t compare, size_t l, size_t r);
static void Swap(void *a, void *b, size_t size);
static void *RecBinarySearchHelper(void *base, size_t l, size_t r, size_t size, cmp_func_t compare, const void *data);

void MergeSort(void *base, size_t nmemb, size_t size, cmp_func_t compare)
{
	assert(base);
	MergeSortHelper(base, size, compare, 0, nmemb - 1);
}

void QuickSort(void *base, size_t nmemb, size_t size, cmp_func_t compare)
{
	assert(base);
	if (0 == nmemb)
	{
		return;
	}
	QuickSortHelper(base, size, compare, 0, nmemb - 1);
}

void *IterBinarySearch(void *base, size_t nmemb, size_t size, cmp_func_t compare, const void *data)
{
	size_t m = 0;
	size_t l = 0;
	size_t r = nmemb - 1;
	assert(base);
	while (l <= r && r != (size_t)-1)
	{
		m = (r - l) / 2;
		if (0 == compare((void *)((size_t)base + (m * size)), data))
		{
			return (void *)data;
		}
		else if (compare(data, (void *)((size_t)base + (m * size))) < 0)
		{
			r = m - 1;
		}
		else
		{
			l = m + 1;
		}
	}
	return NULL;
}

void *RecBinarySearch(void *base, size_t nmemb, size_t size, cmp_func_t compare, const void *data)
{
	assert(base);

	return RecBinarySearchHelper(base, 0, nmemb - 1, size, compare, data);
}

static void *RecBinarySearchHelper(void *base, size_t l, size_t r, size_t size, cmp_func_t compare, const void *data)
{
	size_t m = 0;

	if (l > r || r == (size_t)-1)
	{
		return NULL;
	}
	m = (r - l) / 2;
	if (compare(data, (void *)((size_t)base + (m * size))) < 0)
	{
		return RecBinarySearchHelper(base, l, m - 1, size, compare, data);
	}
	else if (0 == compare((void *)((size_t)base + (m * size)), data))
	{
		return (void *)data;
	}
	else
	{
		return RecBinarySearchHelper(base, m + 1, r, size, compare, data);
	}
}

static void QuickSortHelper(void *base, size_t size, cmp_func_t compare, size_t l, size_t r)
{
	size_t pivot_location = 0;
	if (l < r && r != (size_t)-1)
	{
		pivot_location = QuickSortPartition(base, size, compare, l, r);

		QuickSortHelper(base, size, compare, l, pivot_location - 1);
		QuickSortHelper(base, size, compare, pivot_location + 1, r);
	}
}

static size_t QuickSortPartition(void *base, size_t size, cmp_func_t compare, size_t l, size_t r)
{

	size_t i = l - 1;
	size_t j = 0;

	for (j = l; j <= r; ++j)
	{
		if (compare((void *)((size_t)base + (j * size)), (void *)((size_t)base + (r * size))) < 0)
		{
			++i;
			Swap((void *)((size_t)base + (j * size)), (void *)((size_t)base + (i * size)), size);
		}
	}
	Swap((void *)((size_t)base + (r * size)), (void *)((size_t)base + ((i + 1) * size)), size);
	return i + 1;
}

static void Swap(void *a, void *b, size_t size)
{
	void *temp = NULL;
	temp = malloc(size);
	if (!temp)
	{
		return;
	}
	memcpy(temp, a, size);
	memcpy(a, b, size);
	memcpy(b, temp, size);
	free(temp);
}

static void MergeSortHelper(void *base, size_t size, cmp_func_t compare, size_t l, size_t r)
{
	size_t m = 0;
	if (l < r)
	{
		m = l + (r - l) / 2;

		MergeSortHelper(base, size, compare, l, m);
		MergeSortHelper(base, size, compare, m + 1, r);
		Merge(base, size, compare, l, m, r);
	}
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