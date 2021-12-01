#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "comparisonSorts.h"

static int compare_int(const void *n1, const void *n2);
int main()
{
	int a[] = {34, 53, 32, 7, 0, 100};
	int b[] = {34, 53, 32, 7, 0, 100};
	int c[] = {34, 53, 32, 7, 0, 100};
	int d[] = {34, 53, 32, 7, 0, 100}; /*for qsort*/
	size_t i;
	int e[5000];
	int eb[5000];
	int f[5000];
	int fb[5000];
	int g[5000];
	int gb[5000];

	clock_t start;

	BubbleSort(a, 6);
	if (!(a[0] == 0 && a[1] == 7 && a[2] == 32 &&
		  a[3] == 34 && a[4] == 53 && a[5] == 100))
	{
		printf("fail in %d\n", __LINE__);
	}

	InsertionSort(b, 6);
	if (!(a[0] == 0 && a[1] == 7 && a[2] == 32 &&
		  a[3] == 34 && a[4] == 53 && a[5] == 100))
	{
		printf("fail in %d\n", __LINE__);
	}

	SelectionSort(c, 6);
	if (!(a[0] == 0 && a[1] == 7 && a[2] == 32 &&
		  a[3] == 34 && a[4] == 53 && a[5] == 100))
	{
		printf("fail in %d\n", __LINE__);
	}

	qsort(d, 6, sizeof(*d), compare_int);
	if (!(a[0] == 0 && a[1] == 7 && a[2] == 32 &&
		  a[3] == 34 && a[4] == 53 && a[5] == 100))
	{
		printf("fail in %d\n", __LINE__);
	}
	srand(time(NULL));
	/***************bubble sort***************/
	for (i = 0; i < 5000; ++i)
	{
		e[i] = rand();
		eb[i] = e[i];
	}
	printf("BUBBLE SORT\n");
	start = clock();
	BubbleSort(e, 5000);
	printf("for regular sort\t%lu\n", clock() - start);
	start = clock();
	qsort(eb, 5000, sizeof(*eb), compare_int);
	printf("for qsort\t\t%lu\n", clock() - start);
	printf("\n");
	for (i = 0; i < 5000; ++i)
	{
		if (e[i] != eb[i])
		{
			printf("fail in %d\n", __LINE__);
		}
	}
	/***************insertion sort***************/

	for (i = 0; i < 5000; ++i)
	{
		f[i] = rand();
		fb[i] = f[i];
	}

	printf("INSERTION SORT\n");
	start = clock();
	InsertionSort(f, 5000);
	printf("for regular sort\t%lu\n", clock() - start);
	start = clock();
	qsort(fb, 5000, sizeof(*fb), compare_int);
	printf("for qsort\t\t%lu\n", clock() - start);
	printf("\n");

	for (i = 0; i < 5000; ++i)
	{
		if (f[i] != fb[i])
		{
			printf("fail in %d\n", __LINE__);
		}
	}
	/***************selection sort***************/

	for (i = 0; i < 5000; ++i)
	{
		g[i] = rand();
		gb[i] = g[i];
	}
	printf("SELECTION SORT\n");
	start = clock();
	SelectionSort(g, 5000);
	printf("for regular sort\t%lu\n", clock() - start);
	start = clock();
	qsort(gb, 5000, sizeof(*gb), compare_int);
	printf("for qsort\t\t%lu\n", clock() - start);
	printf("\n");
	for (i = 0; i < 5000; ++i)
	{
		if (g[i] != gb[i])
		{
			printf("fail in %d\n", __LINE__);
		}
	}

	return 0;
}

static int compare_int(const void *n1, const void *n2)
{
	int x = *(const int *)n1;
	int y = *(const int *)n2;
	if (x < y)
	{
		return -1;
	}
	else if (x == y)
	{
		return 0;
	}
	return 1;
}