#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "recursion.h"

static void TestFibonacci(void);
static void TestFlipNode(void);
static void TestStrings(void);
static void TestSortStack(void);

int main()
{
	TestFibonacci();
	TestFlipNode();
	TestStrings();
	TestSortStack();
	return 0;
}

static void TestSortStack(void)
{
	Stack_t *stack = NULL;
	int a1 = 500;
	int a2 = 15;
	int a3 = 9;
	int a4 = 50;
	int a5 = 0;

	stack = StackCreate(100);
	StackPush(stack, &a1);
	StackPush(stack, &a2);
	StackPush(stack, &a3);
	StackPush(stack, &a4);
	StackPush(stack, &a5);
	printf("*********stack before sort********\n");
	PrintStack(stack);
	printf("*********stack after sort********\n");
	SortStack(stack);
	PrintStack(stack);
	StackDestroy(stack);
}

static void TestStrings(void)
{

	char str1[100];
	char str2[100];
	char str3[100];
	char str4[100];
	char str5[100];
	char str6[100];

	if (!(strlen("Hello world!") == Strlen("Hello world!")))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!((strcmp("Hello world!", "") > 0 && Strcmp("Hello world!", "") > 0)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!((strcmp("A", "BFGFDG") < 0 && Strcmp("A", "BFGFDG") < 0)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!((strcmp("Hello world!", "Hello world!") == 0 && Strcmp("Hello world!", "Hello world!") == 0)))
	{
		printf("fail in %d\n", __LINE__);
	}

	Strcpy(str1, "Hello world how are you?????????? ");
	strcpy(str2, "Hello world how are you?????????? ");

	if (!(Strcmp(str1, str2) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	Strcpy(str3, "Dumbeldore Hello wowoww voldemor");
	strcpy(str4, "Dumbeldore Hello wowoww voldemor");

	if (!(Strcmp(strcpy(str4, "Dumbeldore Hello wowoww voldemor"), Strcpy(str4, "Dumbeldore Hello wowoww voldemor")) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(Strcmp(str3, str4) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	Strcat(str1, str3);
	strcat(str2, str4);

	if (!(Strcmp(str1, str2) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	Strcpy(str5, " Hello wowo");
	strcpy(str6, " Hello wowo");
	if (!(Strcmp(Strstr(str1, str5), strstr(str2, str6)) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (Strstr(str1, "Z"))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (Strstr(str1, "Helloooooooooooooooooooooooooooooo"))
	{
		printf("fail in %d\n", __LINE__);
	}
}

static void TestFlipNode(void)
{
	List *list = NULL;

	Node *n1 = NULL;
	Node *n2 = NULL;
	Node *n3 = NULL;
	Node *n4 = NULL;
	Node *n5 = NULL;

	int a1 = 5;
	int a2 = 15;
	int a3 = 90;
	int a4 = 50;
	int a5 = 0;

	n5 = NodeCreateAndInsert(&a5, NULL);
	n4 = NodeCreateAndInsert(&a4, n5);
	n3 = NodeCreateAndInsert(&a3, n4);
	n2 = NodeCreateAndInsert(&a2, n3);
	n1 = NodeCreateAndInsert(&a1, n2);

	list = ListCreateSetHead(n1);
	printf("**********before flip**********\n");
	PrintList(list);
	printf("***********after flip**********\n");
	FlipList(list);
	PrintList(list);
	ListDestroy(list);
}

static void TestFibonacci(void)
{
	if (!(IterativeFibonacci(0) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(IterativeFibonacci(1) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(IterativeFibonacci(5) == 8))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(IterativeFibonacci(15) == 987))
	{
		printf("fail in %d\n", __LINE__);
	}

	/*********************************************/

	if (!(RecursiveFibonacci(0) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(RecursiveFibonacci(1) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(RecursiveFibonacci(5) == 8))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(RecursiveFibonacci(15) == 987))
	{
		printf("fail in %d\n", __LINE__);
	}
}
