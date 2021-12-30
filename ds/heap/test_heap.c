#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "heap.h"

static int CompareInt(const void *n1, const void *n2, const void *param);
static void test1();
static int MatchInt(const void *n1, const void *param);

int main()
{
	test1();

	test2();
	return 0;
}

static void test1()
{
	heap_t *heap = NULL;
	int b[20];
	size_t i = 0;
	int test = 50;
	int test2 = 30;

	srand(time(NULL));
	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		b[i] = rand();
		if (b[i] == test)
		{
			b[i] = i;
		}
		if (b[i] == test2)
		{
			b[i] = i;
		}
	}

	heap = HeapCreate(CompareInt, NULL);

	if (!HeapIsEmpty(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (0 != HeapSize(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	HeapPush(heap, &test);

	if (test != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HeapIsEmpty(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (1 != HeapSize(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	HeapPush(heap, &test2);

	if (test2 != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HeapIsEmpty(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (2 != HeapSize(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	HeapPop(heap);

	if (test != *(int *)HeapPeek(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HeapIsEmpty(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (1 != HeapSize(heap))
	{
		printf("fail in %d\n", __LINE__);
	}

	for (i = 0; i < sizeof(b) / sizeof(*b); ++i)
	{
		HeapPush(heap, &b[i]);
	}

	HeapRemove(heap, MatchInt, &)

		HeapDestroy(heap);
}

static int MatchInt(const void *n1, const void *param)
{
	return *(int *)n1 - *(int *)param;
}

static int CompareInt(const void *n1, const void *n2, const void *param)
{
	(void)param;
	return *(int *)n1 - *(int *)n2;
}