#include <stdio.h>
#include "../../ds/slinkedlist/singly_list.h"
const void *FindNthFromLast(slist_t *list, size_t n);

int main()
{
	int a1 = 4;
	int a2 = 55;
	int a3 = 999;
	slist_t *list = SListCreate();
	SListInsert(SListBegin(list), &a1);
	SListInsert(SListBegin(list), &a2);
	SListInsert(SListBegin(list), &a3);
	printf("%d", *(int *)FindNthFromLast(list, 1));
	return 0;
}

const void *FindNthFromLast(slist_t *list, size_t n)
{
	size_t i = 0;
	slist_iter_t iter = SListBegin(list);
	size_t size = SListCount(list);
	for (; i < size - n; ++i)
	{
		iter = SListIterNext(iter);
	}
	return SListIterGetData(iter);
}
