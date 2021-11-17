#include <stdio.h>
#include <assert.h>
#include "queue.h"
#include "../slinkedlist/singly_list.h"

struct Queue
{
	slist_t *list;
};

/*creat new queue*/
queue_t *QueueCreate(void)
{
	queue_t *queue = NULL;
	queue = (queue_t*)calloc(1, sizeof(queue_t));
	if(!queue)
	{
		return NULL;
	}
	queue->list = SListCreate();
	return queue;
}

/*destroy queue*/
void QueueDestroy(queue_t *queue)
{
	assert(queue);
	SListDestroy(queue->list);
	free(queue);
}

/* insert new item to back of the queue */
void QueueEnqueue(queue_t *queue, const void *val)
{
	assert(queue);
	assert(val);
	SListInsert(SListEnd(queue->list), val);
}

/* pop item from the front of the queue*/
void QueueDequeue(queue_t *queue)
{
	assert(queue);
	SListRemove(SListBegin(queue->list));
}

/*get value of the front item of the queue*/
void *QueuePeek(const queue_t *queue)
{
	assert(queue);
	return SListIterGetData(SListBegin(queue->list));
}

/*return the sizeof queue*/
size_t QueueSize(const queue_t *queue)
{
	assert(queue);
	return SListCount(queue->list);
}

/*check if queue is empty*/
int QueueIsEmpty(const queue_t *queue)	/* return value empty - 1, not empty - 0 */
{
	assert(queue);
	return SListIterIsEqual(SListBegin(queue->list), SListEnd(queue->list));
}





