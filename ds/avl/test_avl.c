#include <stdio.h>
#include "avl.h"
#include <stdlib.h>

static int compare_int(const void *n1, const void *n2, const void *param);
static void EasyTest();
static void HardTest();
static int print_in_order(const void *data, const void *param);

FILE *fp = NULL;

int main()
{
	fp = fopen("test_res.txt", "w");

	EasyTest();
	HardTest();
	fclose(fp);
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
	fprintf(fp, "****************EASY TEST***************\n");
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

	fprintf(fp, "IN_ORDER : print 1 4 5 10\n");
	AvlForEach(avl, print_in_order, NULL, IN_ORDER);

	fprintf(fp, "PRE_ORDER : print 4 1 5 10\n");
	AvlForEach(avl, print_in_order, NULL, PRE_ORDER);

	fprintf(fp, "POST_ORDER : print 1 10 5 4\n");
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

	if (!(AvlHeight(avl) == 2))
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

	if (AvlIsEmpty(avl))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	AvlDestroy(avl);
}

static void HardTest()
{
	int a[10];
	avl_t *avl = NULL;
	size_t i;
	srand(0);

	avl = AvlCreate(compare_int, NULL);
	fprintf(fp, "****************HARD TEST***************\n");

	if (!(AvlSize(avl) == 0))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == 0))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!AvlIsEmpty(avl))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	for (i = 0; i < 10; ++i)
	{
		a[i] = rand() % 1000000;
		printf("%d\n", a[i]);
		AvlInsert(avl, &a[i]);
	}
	if (!(AvlSize(avl) == 10))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (AvlIsEmpty(avl))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	fprintf(fp, "print preorder\n");
	AvlForEach(avl, print_in_order, NULL, IN_ORDER);
	fprintf(fp, "remove %d\n", a[3]);
	AvlRemove(avl, &a[0]);

	if (!(AvlSize(avl) == 9))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	fprintf(fp, "remove %d\n", a[3]);
	AvlRemove(avl, &a[3]);

	if (!(AvlSize(avl) == 8))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	fprintf(fp, "remove %d\n", a[5]);
	AvlRemove(avl, &a[5]);
	fprintf(fp, "remove %d\n", a[7]);
	AvlRemove(avl, &a[7]);
	fprintf(fp, "remove %d\n", a[9]);
	AvlRemove(avl, &a[9]);
	fprintf(fp, "print preorder\n");
	AvlForEach(avl, print_in_order, NULL, IN_ORDER);

	if (!(AvlSize(avl) == 5))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == 3))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	AvlRemove(avl, &a[2]);
	AvlRemove(avl, &a[8]);
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