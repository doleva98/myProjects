
#include <stdio.h>
#include "avl.h"
#include <stdlib.h>
#include <time.h> /* for random */

#define EMPTY_TREE 0 /*change to your height of empty tree*/

static int compare_int(const void *n1, const void *n2, const void *param);
static void EasyTest();
static void HardTest();
static int print_in_order(const void *data, const void *param);
static void test3();
static int Compare(const void *new_elem, const void *curr_elem, const void *param);
static int IsSorted(const void *data, const void *param);
void TestSortLargeAmount();

FILE *fp = NULL;

int main()
{
	FILE *res = NULL;
	fp = fopen("test_res.txt", "w");
	EasyTest();
	HardTest();
	test3();
	fclose(fp);
	system("diff test_res.txt avl_sol.txt > results.txt");
	res = fopen("results.txt", "r");
	if (fgetc(res) == EOF)
	{
		printf("\033[0;32m");
		printf("GOOD JOB PASSED ALL TESTS");
		printf("\033[0m\n");
	}
	else
	{
		printf("\033[0;31m");
		printf("FAILED TEST\n");
		printf("\033[0;35m");

		printf("left: your results\t\t\t\t\t\tright: expected results");

		printf("\033[0m\n");
	}
	system("diff -y --suppress-common-lines test_res.txt avl_sol.txt");
	fclose(res);
	remove("results.txt");
	TestSortLargeAmount();
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

	if (!(AvlHeight(avl) == EMPTY_TREE + 0))
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

	if (!(AvlHeight(avl) == EMPTY_TREE + 1))
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

	if (!(AvlHeight(avl) == EMPTY_TREE + 2))
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

	if (!(AvlHeight(avl) == EMPTY_TREE + 3))
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
	if (!(AvlHeight(avl) == EMPTY_TREE + 2))
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
	if (!(AvlHeight(avl) == EMPTY_TREE + 2))
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
	if (!(AvlHeight(avl) == EMPTY_TREE + 0))
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
		AvlInsert(avl, &a[i]);
	}
	if (!(AvlSize(avl) == 10))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == EMPTY_TREE + 4))
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
	if (!(AvlHeight(avl) == EMPTY_TREE + 4))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	fprintf(fp, "remove %d\n", a[3]);
	AvlRemove(avl, &a[3]);

	if (!(AvlSize(avl) == 8))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == EMPTY_TREE + 4))
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
	if (!(AvlHeight(avl) == EMPTY_TREE + 3))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	fprintf(fp, "remove %d\n", a[1]);
	AvlRemove(avl, &a[1]);
	fprintf(fp, "remove %d\n", a[8]);
	AvlRemove(avl, &a[8]);
	fprintf(fp, "print preorder\n");

	AvlForEach(avl, print_in_order, NULL, IN_ORDER);

	if (!(AvlSize(avl) == 3))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == EMPTY_TREE + 2))
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

static void test3()
{
	avl_t *avl = NULL;
	size_t i = 0;
	int test1;
	int a[100];

	srand(0);
	fprintf(fp, "****************SUPER HARD TEST***************\n");

	avl = AvlCreate(Compare, NULL);

	if (!(AvlSize(avl) == 0))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlIsEmpty(avl)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if (!(AvlHeight(avl) == 0))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	for (; i < 100; ++i)
	{
		a[i] = i;
		AvlInsert(avl, &a[i]);
	}

	if (!(AvlSize(avl) == 100))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if ((AvlIsEmpty(avl)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	if (!(AvlHeight(avl) == 7))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}
	fprintf(fp, "before removal\n");
	AvlForEach(avl, print_in_order, NULL, 0);

	test1 = a[4];
	fprintf(fp, "please remove %d\n", test1);
	AvlRemove(avl, &test1);

	AvlForEach(avl, print_in_order, NULL, 0);
	if (!(AvlSize(avl) == 99))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if ((AvlIsEmpty(avl)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	fprintf(fp, "please remove %d\n", a[9]);

	AvlRemove(avl, &a[9]);

	AvlForEach(avl, print_in_order, NULL, 0);

	if (!(AvlSize(avl) == 98))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if ((AvlIsEmpty(avl)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	fprintf(fp, "please remove %d\n", a[59]);
	AvlRemove(avl, &a[59]);
	AvlForEach(avl, print_in_order, NULL, 0);

	if (!(AvlSize(avl) == 97))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	if ((AvlIsEmpty(avl)))
	{
		fprintf(fp, "fail in %d\n", __LINE__);
	}

	for (i = 85; i < 100; ++i)
	{
		AvlRemove(avl, &a[i]);
	}
	AvlDestroy(avl);
}

static int Compare(const void *new_elem, const void *curr_elem, const void *param)
{
	(void)param;
	return *(int *)new_elem - *(int *)curr_elem;
}

#define ARR_SIZE 1000
static int comp;
void TestSortLargeAmount()
{
	int arr[ARR_SIZE];
	avl_t *avl = NULL;
	size_t i;
	int height = 0;
	srand(time(NULL));
	printf("\n### Testing Sorting large amount of data: %d.\n\n", ARR_SIZE);
	comp = -1;
	avl = AvlCreate(Compare, NULL);
	printf("Height of tree with %d nodes is %d\n\n", 0, (int)AvlHeight(avl));

	printf("\n### Inserting nodes ###\n\n");

	for (i = 0; i < ARR_SIZE; ++i)
	{
		arr[i] = rand();
		AvlInsert(avl, &arr[i]);
		if (AvlHeight(avl) > (size_t)height)
		{
			height = AvlHeight(avl);
			printf("New height %d - updated when inserting node number %lu\n", height, i + 1);
		}
	}
	printf("\n### Height of tree with %d nodes is %d\n", ARR_SIZE, (int)AvlHeight(avl));

	/* checking if elements are sorted */
	AvlForEach(avl, IsSorted, &comp, IN_ORDER);

	printf("\n### Removing all nodes ###\n\n");

	for (i = 0; i < ARR_SIZE; ++i)
	{
		AvlRemove(avl, &arr[i]);
		if (AvlHeight(avl) < (size_t)height)
		{
			height = AvlHeight(avl);
			printf("New height %d - updated when reducing to %lu elements\n", height, ARR_SIZE - i - 1);
		}
	}

	AvlDestroy(avl);
}

static int IsSorted(const void *data, const void *param)
{
	(void)param;
	if (*(int *)data > comp)
	{
		comp = *(int *)data;
		return 1;
	}
	printf("FAILED IN SORTING\n");
	return 0;
}
