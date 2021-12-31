#include <stdio.h>
#include <assert.h>
#include "heap_priority_queue.h"
#include "heap.h"

struct Pri_Queue
{
	heap_t *heap;
};

/*creat new pri_queue*/
extern pri_queue_t *PriQueueCreate(compare_func_t cmp_func, const void *param)
{
	pri_queue_t *pri_queue = NULL;
	pri_queue = (pri_queue_t *)malloc(sizeof(pri_queue_t));

	if (!pri_queue)
	{
		return NULL;
	}

	pri_queue->heap = HeapCreate(cmp_func, param);
	return pri_queue;
}

/*destroy pri_queue*/
extern void PriQueueDestroy(pri_queue_t *pri_queue)
{
	assert(pri_queue);
	HeapDestroy(pri_queue->heap);
	free(pri_queue);
}

/* insert new item to back of the pri_queue */
extern int PriQueueEnqueue(pri_queue_t *pri_queue, const void *data)
{
	assert(pri_queue);
	return HeapPush(pri_queue->heap, data);
}

/* pop item from the front of the pri_queue*/
extern void PriQueueDequeue(pri_queue_t *pri_queue)
{
	HeapPop(pri_queue->heap);
}

/*get value of the front item of the pri_queue*/
extern void *PriQueuePeek(const pri_queue_t *pri_queue)
{
	return HeapPeek(pri_queue->heap);
}

/*return the sizeof pri_queue*/
extern size_t PriQueueSize(const pri_queue_t *pri_queue)
{
	return HeapSize(pri_queue->heap);
}

/*check if pri_queue is empty*/
extern int PriQueueIsEmpty(const pri_queue_t *pri_queue) /* return value empty - 1, not empty - 0 */
{
	return HeapIsEmpty(pri_queue->heap);
}
/*remove all elements*/
extern void PriQueueClear(pri_queue_t *pri_queue)
{
	while (!PriQueueIsEmpty(pri_queue))
	{
		PriQueueDequeue(pri_queue);
	}
}

/*remove elements with a certain UID*/
extern void PriQueueErase(pri_queue_t *pri_queue, is_match_func match_func, const void *param)
{
	HeapRemove(pri_queue->heap, param, match_func);
}
