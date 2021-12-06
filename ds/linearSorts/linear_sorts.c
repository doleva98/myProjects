#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include "linear_sorts.h"
static int GetMax(int *arr, size_t n);
static int *MyCountingSort(int *arr, size_t n, int exp);
static int *NewMyCountingSort(int *arr, size_t n, int exp, size_t bit_number);
#define RADIX 4

int *CountingSort(int *arr, size_t n)
{
	int max = 0;
	int min = 100;
	int size_counter = 0;
	int *counter = NULL;
	int *res = NULL;
	size_t i;
	int j;

	for (i = 0; i < n; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
		if (arr[i] < min)
		{
			min = arr[i];
		}
	}

	size_counter = max - min + 2;
	counter = (int *)calloc(size_counter, sizeof(int));
	if (!counter)
	{
		return NULL;
	}

	res = (int *)malloc(n * sizeof(int));
	if (!res)
	{
		free(counter);
		return NULL;
	}

	for (i = 0; i < n; ++i)
	{
		++counter[arr[i]];
	}

	for (j = 1; j < size_counter; ++j)
	{
		counter[j] += counter[j - 1];
	}

	for (i = 0; i < n; ++i)
	{
		res[counter[arr[n - 1 - i]] - 1] = arr[n - 1 - i];
		--counter[arr[n - 1 - i]];
	}

	for (i = 0; i < n; ++i)
	{
		arr[i] = res[i];
	}
	free(counter);
	free(res);
	return arr;
}

static int *MyCountingSort(int *arr, size_t n, int exp)
{
	int size_counter = 0;
	int *counter = NULL;
	int *res = NULL;
	size_t i;
	int j;

	size_counter = 10;

	counter = (int *)calloc(size_counter, sizeof(int));
	if (!counter)
	{
		return NULL;
	}

	res = (int *)malloc(n * sizeof(int));
	if (!res)
	{
		return NULL;
	}

	for (i = 0; i < n; ++i)
	{
		++counter[(arr[i] / exp) % 10];
	}

	for (j = 1; j < size_counter; ++j)
	{
		counter[j] += counter[j - 1];
	}

	for (i = 0; i < n; ++i)
	{
		res[counter[(arr[n - 1 - i] / exp) % 10] - 1] = arr[n - 1 - i];
		--counter[(arr[n - 1 - i] / exp) % 10];
	}

	for (i = 0; i < n; ++i)
	{
		arr[i] = res[i];
	}
	free(counter);
	free(res);
	return arr;
}

int *RadixSort(int *arr, size_t n)
{
	int exp = 1;
	int max = GetMax(arr, n);
	for (; max / exp > 0; exp *= 10)
	{
		MyCountingSort(arr, n, exp);
	}
	return arr;
}

static int *NewMyCountingSort(int *arr, size_t n, int exp, size_t bit_number)
{
	int size_counter = 0;
	int *counter = NULL;
	int *res = NULL;
	size_t i;
	int j;

	size_counter = 1 << bit_number;

	counter = (int *)calloc(size_counter, sizeof(int));
	if (!counter)
	{
		return NULL;
	}

	res = (int *)malloc(n * sizeof(int));
	if (!res)
	{
		return NULL;
	}

	for (i = 0; i < n; ++i)
	{
		++counter[(arr[i] >> exp) & (size_counter - 1)];
	}

	for (j = 1; j < size_counter; ++j)
	{
		counter[j] += counter[j - 1];
	}

	for (i = 0; i < n; ++i)
	{
		res[counter[(arr[n - 1 - i] >> exp) & (size_counter - 1)] - 1] = arr[n - 1 - i];
		--counter[(arr[n - 1 - i] >> exp) & (size_counter - 1)];
	}

	for (i = 0; i < n; ++i)
	{
		arr[i] = res[i];
	}
	free(counter);
	free(res);
	return arr;
}

int *NewRadixSort(int *arr, size_t n, size_t bit_number)
{
	size_t exp = 0;
	for (; sizeof(arr[0]) * 8 > exp; exp += bit_number)
	{
		NewMyCountingSort(arr, n, exp, bit_number);
	}
	return arr;
}

static int GetMax(int *arr, size_t n)
{
	int max = 0;
	size_t i = 0;
	for (; i < n; ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];
		}
	}
	return max;
}