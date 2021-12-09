#include <stdio.h>
#include "bst.h"
#include <stdlib.h>
#include <time.h>

static int compare_int(const void *n1, const void *n2, const void *param);
static int print_in_order(void *data, const void *param);
static void test10(void);
FILE *fp = NULL;
int main()
{
	bst_t *bst = NULL;
	bst_iter_t iter;
	bst_iter_t iter2;
	bst_iter_t iter4;

	int a = 5;
	int b = 1;
	int c = 4;
	int d = 10;
	int test = 4;

	fp = fopen("test.txt", "w");

	bst = BstCreate(compare_int, NULL);
	fprintf(fp, "****************EASY TEST***************\n");

	if (!(BstSize(bst) == 0))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!BstIsEmpty(bst))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter = BstInsert(bst, &a);

	if (!(BstSize(bst) == 1))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (BstIsEmpty(bst))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(*(int *)BstIterGetData(BstBegin(bst)) == 5))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!BstIterIsEqual(iter, BstBegin(bst)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter2 = BstInsert(bst, &b);
	BstInsert(bst, &c);
	iter4 = BstInsert(bst, &d);
	if (!(BstSize(bst) == 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (BstIsEmpty(bst))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter = BstIterNext(iter);

	if (!BstIterIsEqual(iter4, iter))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter = BstBegin(bst);

	if (!(*(int *)BstIterGetData(iter) == 1))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter = BstIterNext(iter);

	if (!(*(int *)BstIterGetData(iter) == 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter = BstIterNext(iter);

	if (!(*(int *)BstIterGetData(iter) == 5))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter = BstIterNext(iter);

	if (!(*(int *)BstIterGetData(iter) == 10))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter2 = BstIterPrev(BstEnd(bst));

	if (!(*(int *)BstIterGetData(iter2) == 10))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter2 = BstIterPrev(iter2);

	if (!(*(int *)BstIterGetData(iter2) == 5))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	iter2 = BstIterPrev(iter2);

	if (!(*(int *)BstIterGetData(iter2) == 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(*(int *)BstIterGetData(BstFind(bst, &test)) == 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(*(int *)BstIterGetData(BstBegin(bst)) == 1))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	test = 100;
	if (!(BstIterIsEqual(BstFind(bst, &test), BstEnd(bst))))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	fprintf(fp, "before removal\n");

	BstForEach(BstBegin(bst), BstEnd(bst), print_in_order, NULL);

	test = 4;

	BstRemove(BstFind(bst, &test));

	fprintf(fp, "after removal\n");

	BstForEach(BstBegin(bst), BstEnd(bst), print_in_order, NULL);

	BstDestroy(bst);
	test10();
	fclose(fp);
	return 0;
}

static void test10(void)
{
	bst_t *bst = NULL;
	int a[10];
	size_t i = 0;
	int test1;
	srand(0);
	fprintf(fp, "****************HARD TEST***************\n");

	bst = BstCreate(compare_int, NULL);

	if (!(BstSize(bst) == 0))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(BstIsEmpty(bst)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	for (; i < 10; ++i)
	{
		a[i] = rand() % 1000000;
		if (i == 2)
		{
			BstInsert(bst, &a[i]);
			fprintf(fp, "%d\n", a[i]);
		}
		else if (i == 7)
		{
			BstInsert(bst, &a[i]);
		}
		else
		{
			BstInsert(bst, &a[i]);
		}
	}

	if (!(BstSize(bst) == 10))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if ((BstIsEmpty(bst)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	fprintf(fp, "before removal\n");
	BstForEach(BstBegin(bst), BstEnd(bst), print_in_order, NULL);

	test1 = *(int *)BstIterGetData(BstIterNext(BstIterNext(BstBegin(bst))));
	fprintf(fp, "please remove %d\n", test1);
	BstRemove(BstFind(bst, &test1));
	BstForEach(BstBegin(bst), BstEnd(bst), print_in_order, NULL);

	if (!(BstSize(bst) == 9))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if ((BstIsEmpty(bst)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	fprintf(fp, "please remove %d\n", a[9]);
	BstRemove(BstFind(bst, &a[9]));
	BstForEach(BstBegin(bst), BstEnd(bst), print_in_order, NULL);

	if (!(BstSize(bst) == 8))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if ((BstIsEmpty(bst)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	fprintf(fp, "please remove %d\n", a[1]);
	BstRemove(BstFind(bst, &a[1]));

	BstForEach(BstBegin(bst), BstEnd(bst), print_in_order, NULL);

	if (!(BstSize(bst) == 7))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if ((BstIsEmpty(bst)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	BstDestroy(bst);
}

static int compare_int(const void *n1, const void *n2, const void *param)
{
	int x = *(const int *)n1;
	int y = *(const int *)n2;

	(void)param;

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

static int print_in_order(void *data, const void *param)
{
	(void)param;
	fprintf(fp, "%d\n", *(int *)data);
	return 1;
}