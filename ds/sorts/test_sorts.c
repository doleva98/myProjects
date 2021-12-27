#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sorts.h"

static void PrintArray(int *a, size_t len);
static int CompareInt(const void *n1, const void *n2);
static void CheckIfOrdered(int *a, size_t len);
static void CheckMergeSort();

int main()
{
	CheckMergeSort();
	return 0;
}

static void CheckMergeSort()
{
	int a[] = {2, 5, 3, 0, 100, 9898, -8, 86};
	int b[20];
	size_t i = 0;

	srand(time(NULL));
	puts("before sorting");
	PrintArray(a, sizeof(a) / sizeof(*a));
	puts("after sorting");
	MergeSort(a, sizeof(a) / sizeof(*a), sizeof(*a), CompareInt);
	PrintArray(a, sizeof(a) / sizeof(*a));
	CheckIfOrdered(a, sizeof(a) / sizeof(*a));

	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		b[i] = rand();
	}
	MergeSort(b, sizeof(b) / sizeof(*b), sizeof(*b), CompareInt);
	CheckIfOrdered(b, sizeof(b) / sizeof(*b));
}

static void PrintArray(int *a, size_t len)
{
	size_t i = 0;
	for (i = 0; i < len; ++i)
	{
		printf("%d\n", a[i]);
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