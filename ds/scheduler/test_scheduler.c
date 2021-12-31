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
without any valgrin leaks!

any problem contact me on discord, Dolev
*/

#include <stdio.h>
#include "scheduler.h"
#include <stdlib.h>
#include <assert.h>

#define SIZE 10
int Task(const void *param);
int arr[SIZE] = {0};

void TestGeneralFunctionality(scheduler_t *sched);
void TestRun(scheduler_t *sched);

static int task0(const void *param);
static int task1(const void *param);
static int task2(const void *param);
static int task3(const void *param);
static int task_stop(const void *param);
static void test1();

int main()
{

	scheduler_t *sched = NULL;

	test1();

	sched = SchedulerCreate();
	if (NULL == sched)
	{
		return 0;
	}

	TestGeneralFunctionality(sched);
	TestRun(sched);
	SchedulerDestroy(sched);

	return 0;
}

static void test1()
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
	SchedulerTaskAdd(scheduler, task_stop, 15, scheduler);
	/* uid1 = SchedulerTaskAdd(scheduler, task0, 1, "a Death Eater"); */
	/* SchedulerTaskCancel(scheduler, uid1); */

	if (!(SchedulerSize(scheduler) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}

	SchedulerRun(scheduler);

	SchedulerDestroy(scheduler);
}

static int task1(const void *param)
{
	printf("hello i am task1, %s\n", (char *)param);
	return 1;
}

static int task2(const void *param)
{
	printf("hello i am task2, %s\n", (char *)param);
	return 1;
}

static int task3(const void *param)
{
	printf("hello i am task3, %s\n", (char *)param);
	return 1;
}

static int task0(const void *param)
{
	printf("hello i am task0, %s\n", (char *)param);
	return 1;
}

static int task_stop(const void *param)
{
	SchedulerStop((scheduler_t *)param);
	return 0;
}

void TestGeneralFunctionality(scheduler_t *sched)
{
	int a = 1, b = 2, c = 3;
	unique_id_t uid;
	assert(SchedulerIsEmpty(sched));
	uid = SchedulerTaskAdd(sched, Task, 1, &a);
	SchedulerTaskAdd(sched, Task, 2, &b);
	SchedulerTaskAdd(sched, Task, 5, &c);
	assert(3 == SchedulerSize(sched));

	SchedulerTaskCancel(sched, uid);
	assert(2 == SchedulerSize(sched));

	SchedulerClear(sched);
	assert(SchedulerIsEmpty(sched));
}

void TestRun(scheduler_t *sched)
{
	int a = 1, b = 2, c = 3, d = 4, e = 5, f = 6;

	SchedulerTaskAdd(sched, Task, 1, &a);
	SchedulerTaskAdd(sched, Task, 4, &b);
	SchedulerTaskAdd(sched, Task, 5, &c);
	SchedulerTaskAdd(sched, Task, 3, &d);
	SchedulerTaskAdd(sched, Task, 2, &e);
	SchedulerTaskAdd(sched, Task, 1, &f);
	SchedulerRun(sched);
}

int Task(const void *param)
{
	int i;
	printf("Task Nr. %d              progress              [", *(int *)param);
	arr[*(int *)param - 1] = arr[*(int *)param - 1] + 1;
	for (i = 0; i < arr[*(int *)param - 1]; ++i)
	{
		printf("*");
	}
	for (i = 0; i < SIZE - arr[*(int *)param - 1]; ++i)
	{
		printf("/");
	}
	printf("]");
	if (arr[*(int *)param - 1] == SIZE)
	{
		printf("                DONE ");
	}
	printf("\n");
	return arr[*(int *)param - 1] == SIZE ? 0 : 1;
}
