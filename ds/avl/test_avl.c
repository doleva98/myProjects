#include <stdio.h>
#include "avl.h"

static int compare_int(const void *n1, const void *n2, const void *param);
/*static int print_in_order(void *data, const void *param);*/

/*FILE *fp = NULL;*/

int main()
{

	avl_t *avl = NULL;
	int a = 5;
	int b = 1;
	int c = 4;
	int d = 10;
	int test = 4;

	/*fp = fopen("test_res", "w");*/

	avl = AvlCreate(compare_int, NULL);

	if (!AvlIsEmpty(avl))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlSize(avl) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	AvlInsert(avl, &a);

	if (AvlIsEmpty(avl))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlSize(avl) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	AvlInsert(avl, &b);

	if (AvlIsEmpty(avl))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlSize(avl) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	AvlInsert(avl, &c);
	AvlInsert(avl, &d);

	if (AvlIsEmpty(avl))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlSize(avl) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlFind(avl, &d)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(AvlFind(avl, &test)))
	{
		printf("fail in %d\n", __LINE__);
	}

	test = 50;

	if (AvlFind(avl, &test))
	{
		printf("fail in %d\n", __LINE__);
	}
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
/*
static int print_in_order(void *data, const void *param)
{
	(void)param;
	printf("%d\n", *(int *)data);
	return 0;
}*/