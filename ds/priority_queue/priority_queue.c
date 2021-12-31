#include <stdio.h>
#include <assert.h>
#include "priority_queue.h"
#include "sorted_list.h"
struct Pri_Queue
{
	sorted_list_t *list;
};

/*creat new pri_queue*/
pri_queue_t *PriQueueCreate(compare_func_t cmp_func, const void *param)
{
	pri_queue_t *pri_queue = NULL;
	pri_queue = (pri_queue_t *)calloc(1, sizeof(pri_queue_t));

	if (!pri_queue)
	{
		return NULL;
	}

	pri_queue->list = SortedListCreate(cmp_func, param);
	if (!pri_queue->list)
	{
		free(pri_queue);
		return NULL;
	}
	return pri_queue;
}

/*destroy pri_queue*/
void PriQueueDestroy(pri_queue_t *pri_queue)
{
	assert(pri_queue);
	SortedListDestroy(pri_queue->list);
	free(pri_queue);
	pri_queue = NULL;
}

/* insert new item to back of the pri_queue */
int PriQueueEnqueue(pri_queue_t *pri_queue, const void *data)
{
	SortedListInsert(pri_queue->list, data);
	return 1;
}

/* pop item from the front of the pri_queue*/
void PriQueueDequeue(pri_queue_t *pri_queue)
{
	SortedListRemove(SortedListIterPrev(SortedListEnd(pri_queue->list)));
}

/*get value of the front item of the pri_queue*/
void *PriQueuePeek(const pri_queue_t *pri_queue)
{
	return SortedListIterGetData(SortedListIterPrev(SortedListEnd(pri_queue->list)));
}

/*return the sizeof pri_queue*/
size_t PriQueueSize(const pri_queue_t *pri_queue)
{
	return SortedListSize(pri_queue->list);
}

/*check if pri_queue is empty*/
int PriQueueIsEmpty(const pri_queue_t *pri_queue)
{
	return SortedListSize(pri_queue->list) == 0;
} /* return value empty - 1, not empty - 0 */

/*remove all elements*/
void PriQueueClear(pri_queue_t *pri_queue)
{
	while (!SortedListIterIsEqual(SortedListBegin(pri_queue->list), SortedListEnd(pri_queue->list)))
	{
		PriQueueDequeue(pri_queue);
	}
}

/*remove elements with a certain UID*/
void PriQueueErase(pri_queue_t *pri_queue, is_match_func match_func, const void *param)
{
	sorted_list_iter_t iter = SortedListBegin(pri_queue->list);

	while (!SortedListIterIsEqual(iter, SortedListEnd(pri_queue->list)))
	{
		if (match_func(SortedListIterGetData(iter), param))
		{
			SortedListRemove(iter);
			return;
		}
		iter = SortedListIterNext(iter);
	}
}
