#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

static int CompareInt(const void *n1, const void *n2);
static void CheckIfOrdered(int *a, size_t len);
static void CheckMergeSort();
static void CheckQuickSort();
static void Check();

int main()
{
	CheckMergeSort();
	CheckQuickSort();
	Check();
	return 0;
}

void Check()
{
	int arr[] = {3, 6, 7, 5, 3, 5, 6, 2, 9, 1};
	QuickSort(arr, sizeof(arr) / sizeof(*arr), sizeof(*arr), CompareInt);
	CheckIfOrdered(arr, sizeof(arr) / sizeof(*arr));
}

static void CheckQuickSort()
{
	int b[20];
	size_t i = 0;
	int test = 50;

	srand(time(NULL));
	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		b[i] = rand();
		if (b[i] == test)
		{
			b[i] = i;
		}
	}
	QuickSort(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt);
	CheckIfOrdered(b, sizeof(b) / sizeof(*b));
	if (!(b[4] == *(int *)RecBinarySearch(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt, &b[4])))
	{
		printf("fail in %d\n", __LINE__);
	}
	if (test == *(int *)RecBinarySearch(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt, &b[4]))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (RecBinarySearch(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt, &test))
	{
		printf("fail in %d\n", __LINE__);
	}
}

static void CheckMergeSort()
{
	int b[20];
	size_t i = 0;
	int test = 50;
	srand(time(NULL));
	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		b[i] = rand();
		if (b[i] == test)
		{
			b[i] = i;
		}
	}
	MergeSort(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt);
	CheckIfOrdered(b, sizeof(b) / sizeof(*b));
	if (!(b[4] == *(int *)IterBinarySearch(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt, &b[4])))
	{
		printf("fail in %d\n", __LINE__);
	}
	if (test == *(int *)IterBinarySearch(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt, &b[4]))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (IterBinarySearch(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt, &test))
	{
		printf("fail in %d\n", __LINE__);
	}
}

static int CompareInt(const void *n1, const void *n2)
{
	return *(int *)n1 - *(int *)n2;
}

static void CheckIfOrdered(int *a, size_t len)
{
	size_t i = 0;
	for (i = 1; i < len; ++i)
	{
		if (a[i] < a[i - 1])
		{
			printf("fail in %d\n", __LINE__);
		}
	}
}