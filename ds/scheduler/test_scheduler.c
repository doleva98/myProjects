/*output should be

hello i am task2, Voldemort
hello i am task2, Voldemort
hello i am task1, Dumbeldore
hello i am task2, Voldemort
hello i am task3, Harry Potter
hello i am task2, Voldemort
hello i am task1, Dumbeldore
hello i am task2, Voldemort
hello i am task2, Voldemort
hello i am task3, Harry Potter
hello i am task2, Voldemort

it takes 15 seconds for it to fully be printed
without any valgrind leaks!

any problem contact me on discord, Dolev
*/

#include <stdio.h>
#include "scheduler.h"
#include <stdlib.h>

static int task0(const void *param);
static int task1(const void *param);
static int task2(const void *param);
static int task3(const void *param);
static int task_stop(const void *param);

int main()
{

	scheduler_t *scheduler = SchedulerCreate();
	unique_id_t uid1 = uid_null_uid;
	if (!(SchedulerSize(scheduler) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(SchedulerIsEmpty(scheduler) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	scheduler = scheduler;
	SchedulerTaskAdd(scheduler, task1, 5, "Dumbeldore");
	SchedulerTaskAdd(scheduler, task2, 2, "Voldemort");
	SchedulerTaskAdd(scheduler, task3, 7, "Harry Potter");

	if (!(SchedulerSize(scheduler) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(SchedulerIsEmpty(scheduler) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	uid1 = SchedulerTaskAdd(scheduler, task0, 1, "a Death Eater");
	SchedulerTaskCancel(scheduler, uid1);

	if (!(SchedulerSize(scheduler) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}

	SchedulerTaskAdd(scheduler, task_stop, 15, scheduler);

	SchedulerClear(scheduler);

	if (!(SchedulerSize(scheduler) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(SchedulerIsEmpty(scheduler) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	SchedulerTaskAdd(scheduler, task1, 5, "Dumbeldore");
	SchedulerTaskAdd(scheduler, task2, 2, "Voldemort");
	SchedulerTaskAdd(scheduler, task3, 7, "Harry Potter");
	SchedulerTaskAdd(scheduler, task_stop, 14, scheduler);
	uid1 = SchedulerTaskAdd(scheduler, task0, 1, "a Death Eater");
	SchedulerTaskCancel(scheduler, uid1);

	if (!(SchedulerSize(scheduler) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}

	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
	return 0;
}

static int task1(const void *param)
{
	printf("hello i am task1, %s\n", (char *)param);
	return 0;
}

static int task2(const void *param)
{
	printf("hello i am task2, %s\n", (char *)param);
	return 0;
}

static int task3(const void *param)
{
	printf("hello i am task3, %s\n", (char *)param);
	return 0;
}

static int task0(const void *param)
{
	printf("hello i am task0, %s\n", (char *)param);
	return 0;
}

static int task_stop(const void *param)
{
	SchedulerStop((scheduler_t *)param);
	return 1;
}
