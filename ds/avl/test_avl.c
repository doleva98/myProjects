#include <stdio.h>
#include "avl.h"

static int compare_int(const void *n1, const void *n2, const void *param);
static void EasyTest();

static int print_in_order(const void *data, const void *param);

FILE *fp = NULL;

int main()
{
	fp = fopen("test_res", "w");

	EasyTest();
	return 0;
}

static void EasyTest()
{

	avl_t *avl = NULL;
	int a = 5;
	int b = 1;
	int c = 4;
	int d = 10;
	int test = 4;

	avl = AvlCreate(compare_int, NULL);

	if (!AvlIsEmpty(avl))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlSize(avl) == 0))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 0))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	AvlInsert(avl, &a);
	fprintf(fp, "print 5\n");
	AvlForEach(avl, print_in_order, NULL, IN_ORDER);

	if (AvlIsEmpty(avl))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlSize(avl) == 1))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 1))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	AvlInsert(avl, &b);
	fprintf(fp, "print 1 5\n");
	AvlForEach(avl, print_in_order, NULL, IN_ORDER);

	if (AvlIsEmpty(avl))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlSize(avl) == 2))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 2))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	AvlInsert(avl, &c);
	AvlInsert(avl, &d);

	fprintf(fp, "print 1 4 5 10\n");
	AvlForEach(avl, print_in_order, NULL, IN_ORDER);

	fprintf(fp, "print 5 1 4 10\n");
	AvlForEach(avl, print_in_order, NULL, PRE_ORDER);

	fprintf(fp, "print 4 1 10 5\n");
	AvlForEach(avl, print_in_order, NULL, POST_ORDER);

	if (AvlIsEmpty(avl))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlSize(avl) == 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 3))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlFind(avl, &d)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlFind(avl, &test)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	test = 50;

	if (AvlFind(avl, &test))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	test = 5;
	AvlRemove(avl, &test);

	fprintf(fp, "print 1 4 10\n");
	AvlForEach(avl, print_in_order, NULL, IN_ORDER);

	if (!(AvlSize(avl) == 3))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == 3))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	test = 4;

	AvlRemove(avl, &test);

	fprintf(fp, "print 1 10\n");
	AvlForEach(avl, print_in_order, NULL, IN_ORDER);

	if (!(AvlSize(avl) == 2))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == 2))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	AvlDestroy(avl);
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

static int print_in_order(const void *data, const void *param)
{
	(void)param;
	fprintf(fp, "%d\n", *(int *)data);
	return 0;
}