#include <stdio.h>
#include "bst.h"

static int compare_int(const void *n1, const void *n2, const void *param);
static int print_in_order(void *data, const void *param);

int main()
{
	bst_t *bst = NULL;
	bst_iter_t iter;
	bst_iter_t iter2;
	bst_iter_t iter3;
	bst_iter_t iter4;

	int a = 5;
	int b = 1;
	int c = 4;
	int d = 10;
	int test = 4;

	bst = BstCreate(compare_int, NULL);

	if (!(BstSize(bst) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	/*if (!BstIsEmpty(bst))
	{
		printf("fail in %d\n", __LINE__);
	}

	/*iter = BstInsert(bst, &a);

	if (!(BstSize(bst) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (BstIsEmpty(bst))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(*(int *)BstIterGetData(BstBegin(bst)) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!BstIterIsEqual(iter, BstBegin(bst)))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter2 = BstInsert(bst, &b);
	iter3 = BstInsert(bst, &c);
	iter4 = BstInsert(bst, &d);

	if (!(BstSize(bst) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (BstIsEmpty(bst))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter = BstIterNext(iter);

	if (!BstIterIsEqual(iter4, iter2))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter = BstBegin(bst);

	if (!(*(int *)BstIterGetData(iter) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter = BstIterNext(iter);

	if (!(*(int *)BstIterGetData(iter) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter = BstIterNext(iter);

	if (!(*(int *)BstIterGetData(iter) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter = BstIterNext(iter);

	if (!(*(int *)BstIterGetData(iter) == 10))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter2 = BstIterPrev(BstEnd(bst));

	if (!(*(int *)BstIterGetData(iter2) == 10))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter2 = BstIterPrev(iter2);

	if (!(*(int *)BstIterGetData(iter2) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}

	iter2 = BstIterPrev(iter2);

	if (!(*(int *)BstIterGetData(iter2) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}
	iter2 = BstIterPrev(iter2);

	if (!(*(int *)BstIterGetData(iter2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(BstIterIsEqual(BstFind(bst, &test), iter3)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(*(int *)BstIterGetData(iter2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
*/
	return 0;
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
	printf("%d", *(int *)data);
	return 1;
}