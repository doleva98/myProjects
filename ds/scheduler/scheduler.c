#include <stdio.h>
#include <unistd.h>
#include "scheduler.h"
#include "heap_priority_queue.h"
#include <stdlib.h>

static int Compare(const void *new_elem, const void *curr_elem, const void *param);
static int SameUid(const void *curr_item, const void *param);
static void clearAll(scheduler_t *scheduler);
static int RUN = 1;

struct scheduler
{
	pri_queue_t *queue;
};

typedef struct
{
	task_func_t task;
	unique_id_t uid;
	size_t interval;
	const void *param;
} task_t;

/*creates new scheduler engine*/
scheduler_t *SchedulerCreate()
{
	int isUp = 1;
	scheduler_t *scheduler = NULL;

	scheduler = (scheduler_t *)calloc(sizeof(scheduler_t), 1);
	if (!scheduler)
	{
		return NULL;
	}
	scheduler->queue = PriQueueCreate(Compare, &isUp);
	if (!scheduler->queue)
	{
		free(scheduler);
		return NULL;
	}
	return scheduler;
}

/*destroy scheduler*/
void SchedulerDestroy(scheduler_t *scheduler)
{
	clearAll(scheduler);
	PriQueueDestroy(scheduler->queue);
	free(scheduler);
}

/* insert new task to the scheduler engine*/
unique_id_t SchedulerTaskAdd(scheduler_t *scheduler, task_func_t task,
							 size_t interval_in_secs, const void *param)
{
	task_t *new_task = NULL;
	new_task = (task_t *)calloc(sizeof(task_t), 1);
	if (!new_task)
	{
		return uid_null_uid;
	}

	new_task->task = task;
	new_task->uid = UIDGenerate();
	new_task->interval = interval_in_secs;
	new_task->param = param;

	if (PriQueueEnqueue(scheduler->queue, new_task))
	{
		return uid_null_uid;
	}

	return new_task->uid;
}

/* remove task from scheduler engine*/
void SchedulerTaskCancel(scheduler_t *scheduler, unique_id_t uid)
{
	PriQueueErase(scheduler->queue, SameUid, &uid);
}

/* run the scheduler engine */
int SchedulerRun(scheduler_t *scheduler)
{
	task_t *curr_task;
	size_t curr_time;
	while (RUN)
	{
		curr_time = time(NULL);
		curr_task = (task_t *)PriQueuePeek(scheduler->queue);
		PriQueueDequeue(scheduler->queue);
		sleep(curr_task->interval + getTime(curr_task->uid) - curr_time);
		if (0 == curr_task->task(curr_task->param))
		{
			SchedulerTaskAdd(scheduler, curr_task->task, curr_task->interval, curr_task->param);
		}
		free(curr_task);
	}
	return 1;
}

/* stop running scheduler */
void SchedulerStop(scheduler_t *scheduler)
{
	(void)scheduler;
	RUN = 0;
}

/* return the size of the scheduler */
size_t SchedulerSize(scheduler_t *scheduler)
{
	return PriQueueSize(scheduler->queue);
}

/*check if scheduler is empty*/
int SchedulerIsEmpty(scheduler_t *scheduler)
{
	return PriQueueIsEmpty(scheduler->queue);
}

/*clears all the scheduler*/
void SchedulerClear(scheduler_t *scheduler)
{
	clearAll(scheduler);
	PriQueueClear(scheduler->queue);
}

static int Compare(const void *curr_elem, const void *new_elem, const void *param)
{
	size_t curr_time = time(NULL);
	size_t new_interval = ((task_t *)new_elem)->interval;
	size_t new_time = (size_t)((task_t *)new_elem)->uid.timestamp;

	size_t curr_interval = ((task_t *)curr_elem)->interval;
	size_t curr_elem_time = (size_t)((task_t *)curr_elem)->uid.timestamp;
	int isUp = *(int *)param;

	if (isUp)
	{
		return -((new_interval + new_time - curr_time) - (curr_interval + curr_elem_time - curr_time));
	}
	return (new_interval + new_time - curr_time) - (curr_interval + curr_elem_time - curr_time);
}

static int SameUid(const void *curr_item, const void *param)
{
	if (UIDIsEqual(((task_t *)curr_item)->uid, *(unique_id_t *)param))
	{
		free((void *)curr_item);
		return 0;
	}
	return 1;
}

static void clearAll(scheduler_t *scheduler)
{
	while (!SchedulerIsEmpty(scheduler))
	{
		free(PriQueuePeek(scheduler->queue));
		PriQueueDequeue(scheduler->queue);
	}
}
