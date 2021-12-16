#include <stdio.h>
#include "recursion.h"
#include <stdlib.h>
#include "stack.h"

static Node *FlipListWithNode(List *list, Node *node);
static void SortInsert(Stack_t *stack, void *element);

struct node_t
{
	const void *data;
	Node *next;
};

struct list_t
{
	Node *head;
};

int IterativeFibonacci(int element_index)
{
	int before = 1;
	int res = 1;
	int temp = 0;
	int i = 0;

	for (i = 1; i < element_index; ++i)
	{
		temp = res;
		res += before;
		before = temp;
	}

	return res;
}
int RecursiveFibonacci(int element_index)
{

	if (element_index == 0 || element_index == 1)
	{
		return 1;
	}
	return RecursiveFibonacci(element_index - 1) + RecursiveFibonacci(element_index - 2);
}

List *ListCreateSetHead(Node *node)
{
	List *list = NULL;

	list = (List *)malloc(sizeof(List));
	if (!list)
	{
		return NULL;
	}

	list->head = node;
	return list;
}

void PrintList(List *list)
{
	Node *curr = list->head;
	while (curr)
	{
		printf("%d\n", *(int *)NodeGetData(curr));
		curr = curr->next;
	}
}

Node *NodeCreateAndInsert(const void *data, Node *next)
{
	Node *node = NULL;

	node = (Node *)malloc(sizeof(Node));
	if (!node)
	{
		return NULL;
	}
	node->data = data;
	node->next = next;
	return node;
}

const void *NodeGetData(Node *Node)
{
	return Node->data;
}

List *FlipList(List *list)
{
	FlipListWithNode(list, list->head);
	return list;
}

static Node *FlipListWithNode(List *list, Node *node)
{
	Node *next_node = NULL;
	if (!node)
	{
		return NULL;
	}
	if (!node->next)
	{
		list->head = node;
	}
	next_node = FlipListWithNode(list, node->next);
	if (next_node)
	{
		next_node->next = node;
		node->next = NULL;
	}
	return node;
}

void ListDestroy(List *list)
{
	Node *temp = NULL;

	while (list->head)
	{
		temp = list->head;
		list->head = list->head->next;
		free(temp);
	}
	free(list);
}

/******************STRINGS*************/

size_t Strlen(const char *str)
{
	if (!*str)
	{
		return 0;
	}
	return 1 + Strlen(str + 1);
}

int Strcmp(const char *str1, const char *str2)
{
	if (*str1 != *str2)
	{
		return *str1 - *str2;
	}
	if (!*str1)
	{
		return 0;
	}
	return Strcmp(str1 + 1, str2 + 1);
}

char *Strcpy(char *dest, const char *src)
{
	*dest = *src;
	if (!*src)
	{
		return dest;
	}
	return Strcpy(dest + 1, src + 1) - 1;
}

char *Strcat(char *dest, const char *src)
{
	if (!*dest)
	{
		if (!*src)
		{
			return dest;
		}
		*dest = *src++;
		*(dest + 1) = '\0';
	}
	return Strcat(dest + 1, src) - 1;
}

char *Strstr(const char *haystack, const char *needle)
{
	if (!*needle)
	{
		return (char *)haystack;
	}
	if (!*haystack)
	{
		return NULL;
	}
	if (*haystack == *needle &&
		Strstr(haystack + 1, needle + 1) == haystack + 1)
	{
		return (char *)haystack;
	}
	return Strstr(haystack + 1, needle);
}

/******************SORT STACK*******************/

void PrintStack(Stack_t *stack)
{
	Stack_t *temp = StackCreate(StackSize(stack));
	while (!StackIsEmpty(stack))
	{
		printf("%d\n", *(int *)StackPeek(stack));
		StackPush(temp, StackPeek(stack));
		StackPop(stack);
	}
	while (!StackIsEmpty(temp))
	{
		StackPush(stack, StackPeek(temp));
		StackPop(temp);
	}
	StackDestroy(temp);
}

Stack_t *SortStack(Stack_t *stack)
{
	if (!StackIsEmpty(stack))
	{
		void *temp = StackPeek(stack);
		StackPop(stack);
		SortStack(stack);
		SortInsert(stack, temp);
	}
	return stack;
}

static void SortInsert(Stack_t *stack, void *element)
{
	if (StackIsEmpty(stack) || *(int *)element > *(int *)StackPeek(stack))
	{
		StackPush(stack, element);
	}
	else
	{
		void *temp = StackPeek(stack);
		StackPop(stack);
		SortInsert(stack, element);
		StackPush(stack, temp);
	}
}