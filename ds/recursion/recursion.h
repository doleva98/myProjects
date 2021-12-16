#ifndef _RECURSION_H_
#define _RECURSION_H_

#include "stack.h"

typedef struct list_t List;
typedef struct node_t Node;

int IterativeFibonacci(int element_index);
int RecursiveFibonacci(int element_index);

List *ListCreateSetHead(Node *node);
Node *NodeCreateAndInsert(const void *data, Node *next);
const void *NodeGetData(Node *Node);
void PrintList(List *list);
List *FlipList(List *list);
void ListDestroy(List *list);

size_t Strlen(const char *str);
int Strcmp(const char *str1, const char *str2);
char *Strcpy(char *dest, const char *src);
char *Strcat(char *dest, const char *src);
char *Strstr(const char *haystack, const char *needle);
Stack_t *SortStack(Stack_t *stack);
void PrintStack(Stack_t *stack);

#endif
