#include <stdio.h>
#include <assert.h>
#include "doubly_linked_list.h"

static int PlusOne(void *data, void *param);

struct DList
{
	dnode_t *head;
	dlist_iter_t *IterHead;
};

struct DListNode
{
	const void *data;
	dnode_t *next;
	dnode_t *prev;
};

/* Create new list */
dlist_t *DListCreate()
{

	dlist_t *list = NULL;
	list = (dlist_t *)calloc(1, sizeof(dlist_t));

	if (!list)
	{
		return NULL;
	}

	list->head = (dnode_t *)calloc(1, sizeof(dnode_t)); /*dummy*/
	if (!list->head)
	{
		free(list);
		return NULL;
	}

	list->head->data = NULL;
	list->head->next = NULL;
	list->head->prev = NULL;

	list->IterHead = (dlist_iter_t *)calloc(1, sizeof(dlist_iter_t));
	if (!list->IterHead)
	{
		free(list->head);
		free(list);
		return NULL;
	}
	list->IterHead->node = list->head;
	list->IterHead->list = list;
	return list;
}

/* Delete the list */

void DListDestroy(dlist_t *list)
{
	dlist_iter_t iter = DListBegin(list);
	assert(list);

	while (iter.node->next)
	{
		DListRemove(iter);
	}

	free(list->head);
	list->head = NULL;
	free(list->IterHead);
	list->IterHead = NULL;
	free(list);
}

dlist_iter_t DListBegin(dlist_t *list)
{
	assert(list);
	return *list->IterHead;
}

dlist_iter_t DListEnd(dlist_t *list)
{
	dlist_iter_t iter = DListBegin(list);
	assert(list);
	for (; iter.node->next != NULL; iter = DListIterNext(iter))
	{
	}
	return iter;
}

dlist_iter_t DListInsert(dlist_iter_t iter, const void *item)
{
	dnode_t *temp = NULL;
	assert(iter.node);
	temp = (dnode_t *)calloc(1, sizeof(dnode_t));
	if (!temp)
	{
		return iter;
	}
	temp->data = iter.node->data;
	iter.node->data = item;

	temp->next = iter.node->next;

	iter.node->next = temp;
	temp->prev = iter.node;
	if (temp->next)
	{
		temp->next->prev = temp;
	}
	return iter;
}

void DListRemove(dlist_iter_t iter)
{
	dnode_t *temp = iter.node->next;
	assert(iter.node);
	if (NULL == iter.node->next)
	{
		return;
	}
	iter.node->data = temp->data;
	iter.node->next = temp->next;

	if (iter.node->next)
	{
		iter.node->next->prev = iter.node;
	}

	free(temp);
}

size_t DListCount(dlist_t *list)
{
	size_t count = 0; /*counts the dummmy head*/
	dlist_iter_t iter = DListBegin(list);

	assert(list);

	for (; !DListIterIsEqual(iter, DListEnd(list)); iter = DListIterNext(iter))
	{
		++count;
	}

	return count;
}

dlist_iter_t DListIterNext(dlist_iter_t iter)
{
	assert(iter.node);
	iter.node = iter.node->next;
	return iter;
}

dlist_iter_t DListIterPrev(dlist_iter_t iter)
{
	assert(iter.node);

	iter.node = iter.node->prev;
	return iter;
}

int DListIterIsEqual(dlist_iter_t iter1, dlist_iter_t iter2)
{
	return iter1.node == iter2.node;
}

void *DListIterGetData(dlist_iter_t iter)
{

	return (void *)iter.node->data;
}

dlist_iter_t DListFind(dlist_iter_t from, dlist_iter_t to, match_func_t is_match_func, void *param)
{

	for (; !DListIterIsEqual(from, to); from = DListIterNext(from))
	{
		if (is_match_func((void *)from.node->data, param))
		{
			return from;
		}
	}
	return DListEnd(from.list);
}

int DListForEach(dlist_iter_t from, dlist_iter_t to, action_func_t action_func, void *param)
{

	for (; !DListIterIsEqual(from, to); from = DListIterNext(from))
	{
		if (!action_func((void *)from.node->data, param))
		{
			return 0;
		}
	}
	return 1;
}

size_t DListCountForEach(dlist_t *list)
{
	size_t count = 0;

	DListForEach(DListBegin(list), DListEnd(list), PlusOne, &count);
	return count;
}

static int PlusOne(void *data, void *param)
{
	(void)data;
	++*(size_t *)param;
	return 1;
}

size_t DListSize(dlist_t *list)
{
	return DListCount(list);
}

dlist_iter_t DListPushFront(dlist_t *list, const void *data)
{
	DListInsert(DListBegin(list), data);
	return DListBegin(list);
}

dlist_iter_t DListPushBack(dlist_t *list, const void *data)
{
	DListInsert(DListEnd(list), data);
	return DListEnd(list);
}

void *DListPopFront(dlist_t *list)
{
	dlist_iter_t iter = DListBegin(list);
	void *data = (void *)iter.node->data;
	DListRemove(iter);
	return data;
}

void *DListPopBack(dlist_t *list)
{
	void *data = NULL;
	dlist_iter_t iter = DListEnd(list);
	iter.node = iter.node->prev;
	data = (void *)iter.node->data;
	DListRemove(iter);
	return data;
}

dlist_iter_t DListSplice(dlist_iter_t where,
						 dlist_iter_t begin,
						 dlist_iter_t end)
{
	dlist_t *prevlist = begin.list;
	dnode_t *tempBefore = begin.node->prev;
	dnode_t *tempAfter = end.node->next;

	if (where.node->prev)
	{
		where.node->prev->next = begin.node;
		begin.node->prev = where.node->prev;
	}
	else
	{
		where.list->head = begin.node;
		where.list->IterHead->node = begin.node;
	}

	where.node->prev = end.node;
	end.node->next = where.node;
	if (tempBefore)
	{
		tempBefore->next = tempAfter;
	}
	else
	{
		if (tempAfter->next)
		{
			prevlist->head = tempAfter;
			prevlist->IterHead->node = tempAfter;
		}
	}

	return end;
}
