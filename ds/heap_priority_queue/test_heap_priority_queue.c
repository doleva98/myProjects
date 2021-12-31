#include <stdio.h>
#include <string.h>
#include "heap_priority_queue.h"
#include <assert.h>

typedef struct Person
{
	char name[50];
	size_t id;
	size_t u_id;
} Person_t;
/*************DOLEV TESTS TYPEDEF**********/
typedef struct
{
	int numId;
	char name[50];
} person_t;
/**********END OF DOLEV TYPEDEF********************/

/**********MATAN TESTS TYPEDEF&FUNCS***************/
typedef struct
{
	int priority;
	int assignment_code;
} assignment_t;

enum priorities
{
	URGENT,
	CASUAL,
	NON_URGENT
};

int Match(const void *curr_item, const void *param);
int Compare(const void *new_elem, const void *curr_elem, const void *param);
void PrintJob(assignment_t *job);
/*********END OF MATAN TESTS TYPEDEF&FUNCS*********/

int PrintPerson(void *data, void *param)
{
	size_t id = ((Person_t *)data)->id;
	char *name = ((Person_t *)data)->name;
	printf("Person n.%lu Name: %s ID: %lu \n", *(size_t *)param, name, id);
	(*(size_t *)param)++;
	return 1;
}

int isBefore(const void *data1, const void *data2, const void *param)
{
	int i1 = (int)((Person_t *)data1)->id;
	int i2 = (int)((Person_t *)data2)->id;
	(void)param;
	return i1 - i2;
}

int isMatch(const void *data, const void *param)
{
	size_t u_id;
	u_id = ((Person_t *)data)->u_id;

	return u_id == *(size_t *)param;
}

static int IsLower(const void *new_elem, const void *curr_elem, const void *param);
static int match(const void *data, const void *param);
int TestDolev(void)
{
	int IsUpParam = 1;
	pri_queue_t *queue = PriQueueCreate(IsLower, &IsUpParam);
	person_t p1;
	person_t p2;
	person_t p3;
	person_t p4;
	int test;
	p1.numId = 1;
	strcpy(p1.name, "Dumbeldore");

	p2.numId = 2;
	strcpy(p2.name, "Harry Potter");

	p3.numId = 3;
	strcpy(p3.name, "Ronald Wiseley");

	p4.numId = 8;
	strcpy(p4.name, "Hermione Granger");

	if (!(PriQueueSize(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(PriQueueIsEmpty(queue) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	PriQueueEnqueue(queue, &p3); /*3*/

	if (!(((person_t *)PriQueuePeek(queue))->numId == 3))
	{
		printf("fail in %d\n", __LINE__);
	}

	PriQueueEnqueue(queue, &p1); /*1,3*/

	if (!(((person_t *)PriQueuePeek(queue))->numId == 3))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(PriQueueSize(queue) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	PriQueueDequeue(queue); /*1*/

	if (!(((person_t *)PriQueuePeek(queue))->numId == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(PriQueueSize(queue) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(PriQueueIsEmpty(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(strcmp(((person_t *)PriQueuePeek(queue))->name, "Dumbeldore") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	PriQueueEnqueue(queue, &p4);
	PriQueueEnqueue(queue, &p2); /*1,2,4*/

	if (!(((person_t *)PriQueuePeek(queue))->numId == 8))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(strcmp(((person_t *)PriQueuePeek(queue))->name, "Hermione Granger") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(PriQueueSize(queue) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}

	test = 2;

	PriQueueErase(queue, match, &test); /*1,4*/

	if (!(PriQueueSize(queue) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	test = 8;

	PriQueueErase(queue, match, &test); /*1*/

	if (!(((person_t *)PriQueuePeek(queue))->numId == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(strcmp(((person_t *)PriQueuePeek(queue))->name, "Dumbeldore") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	PriQueueEnqueue(queue, &p2);
	PriQueueEnqueue(queue, &p3);
	PriQueueEnqueue(queue, &p4);

	if (!(strcmp(((person_t *)PriQueuePeek(queue))->name, "Hermione Granger") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(PriQueueSize(queue) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}

	PriQueueClear(queue);

	if (!(PriQueueSize(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(PriQueueIsEmpty(queue) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	PriQueueEnqueue(queue, &p2);
	PriQueueEnqueue(queue, &p3);

	if (!(PriQueueSize(queue) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(strcmp(((person_t *)PriQueuePeek(queue))->name, "Ronald Wiseley") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(PriQueueIsEmpty(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	PriQueueDestroy(queue);
	return 0;
}

static int IsLower(const void *new_elem, const void *curr_elem, const void *param)
{
	int num1, num2, IsLowToHigh;
	if (!curr_elem)
	{
		return 1;
	}
	num1 = ((person_t *)new_elem)->numId;
	num2 = ((person_t *)curr_elem)->numId;
	IsLowToHigh = *(int *)param;
	if (IsLowToHigh)
	{
		return num1 <= num2;
	}
	else
	{
		return num2 <= num1;
	}
}
int TestMatan(void)
{
	pri_queue_t *p_queue = NULL;
	size_t i;
	assignment_t *current;

	assignment_t jobs[11];
	jobs[0].priority = CASUAL;
	jobs[0].assignment_code = 1;
	jobs[1].priority = NON_URGENT;
	jobs[1].assignment_code = 2;
	jobs[2].priority = CASUAL;
	jobs[2].assignment_code = 3;
	jobs[3].priority = NON_URGENT;
	jobs[3].assignment_code = 4;
	jobs[4].priority = URGENT;
	jobs[4].assignment_code = 5;
	jobs[5].priority = NON_URGENT;
	jobs[5].assignment_code = 6;
	jobs[6].priority = NON_URGENT;
	jobs[6].assignment_code = 7;
	jobs[7].priority = CASUAL;
	jobs[7].assignment_code = 8;
	jobs[8].priority = NON_URGENT;
	jobs[8].assignment_code = 9;
	jobs[9].priority = URGENT;
	jobs[9].assignment_code = 10;
	jobs[10].priority = NON_URGENT;
	jobs[10].assignment_code = 11;

	p_queue = PriQueueCreate(Compare, NULL);

	for (i = 0; i < 11; ++i)
	{
		PriQueueEnqueue(p_queue, &jobs[i]);
	}
	PriQueueClear(p_queue);
	assert(PriQueueIsEmpty(p_queue));

	puts("Enqueue: ");
	puts("");
	printf("Size of priority queue %lu\n\n", PriQueueSize(p_queue));
	for (i = 0; i < 11; ++i)
	{
		PrintJob(&jobs[i]);
		PriQueueEnqueue(p_queue, &jobs[i]);
	}
	puts("");

	printf("PriQueueErase - looking for assignment code %d\n", jobs[2].assignment_code);
	PriQueueErase(p_queue, Match, &jobs[2].assignment_code);

	printf("Size of priority queue %lu\n\n", PriQueueSize(p_queue));
	puts("Dequeue: ");
	for (i = 0; i < 10; ++i)
	{
		current = PriQueuePeek(p_queue);
		PrintJob(current);
		PriQueueDequeue(p_queue);
	}
	printf("\nSize of priority queue %lu\n", PriQueueSize(p_queue));
	assert(PriQueueIsEmpty(p_queue));
	PriQueueDestroy(p_queue);
	return 0;
}

int Compare(const void *new_elem, const void *curr_elem, const void *param)
{
	(void)param;
	return *(int *)new_elem < *(int *)curr_elem;
}

void PrintJob(assignment_t *job)
{
	printf("assignment code = %d \nPriority:                 ", job->assignment_code);
	switch (job->priority)
	{
	case URGENT:
		printf("URGENT\n");
		break;
	case CASUAL:
		printf("CASUAL\n");
		break;
	case NON_URGENT:
		printf("NON_URGENT\n");
		break;
	}
}

int Match(const void *curr_item, const void *param)
{
	const assignment_t *temp;
	temp = curr_item;
	return temp->assignment_code == *(int *)param;
}

static int match(const void *data, const void *param)
{
	int num1, num2;

	num1 = ((person_t *)data)->numId;
	num2 = *(int *)param;
	return num1 == num2;
}
int main()
{
	pri_queue_t *pqueue = NULL;
	Person_t p[5] = {{"Daniel", 123, 0}, {"Dolev", 2, 1}, {"Matan", 130, 2}, {"Omer", 150, 3}, {"Rona", 71, 4}};
	size_t param = 1;
	size_t i = 0;
	size_t u_id = 0;

	i = 0;
	pqueue = PriQueueCreate(isBefore, &param);
	if (PriQueueSize(pqueue) != 0)
	{
		printf("ERROR IN LINE %d\n", __LINE__);
	}
	if (!PriQueueIsEmpty(pqueue))
	{
		printf("ERROR IN LINE %d\n", __LINE__);
	}

	PriQueueEnqueue(pqueue, &p[0]);
	PriQueueEnqueue(pqueue, &p[1]);
	PriQueueEnqueue(pqueue, &p[2]);
	PriQueueEnqueue(pqueue, &p[3]);
	PriQueueEnqueue(pqueue, &p[4]);
	if (PriQueueIsEmpty(pqueue))
	{
		printf("ERROR IN LINE %d\n", __LINE__);
	}
	if (PriQueueSize(pqueue) != 5)
	{
		printf("ERROR IN LINE %d\n", __LINE__);
	}
	while (i < 5)
	{
		PrintPerson(PriQueuePeek(pqueue), &i);
		PriQueueDequeue(pqueue);
	}
	if (PriQueueSize(pqueue) != 0)
	{
		printf("ERROR IN LINE %d\n", __LINE__);
	}

	PriQueueEnqueue(pqueue, &p[0]);
	PriQueueEnqueue(pqueue, &p[1]);
	PriQueueEnqueue(pqueue, &p[2]);
	PriQueueEnqueue(pqueue, &p[3]);
	PriQueueEnqueue(pqueue, &p[4]);

	PriQueueClear(pqueue);
	if (PriQueueSize(pqueue) != 0 || !PriQueueIsEmpty(pqueue))
	{
		printf("ERROR IN LINE %d\n", __LINE__);
	}
	PriQueueEnqueue(pqueue, &p[0]);
	PriQueueEnqueue(pqueue, &p[1]);
	PriQueueEnqueue(pqueue, &p[2]);
	PriQueueEnqueue(pqueue, &p[3]);
	PriQueueEnqueue(pqueue, &p[4]);

	PriQueueErase(pqueue, isMatch, &u_id);
	i = 0;
	printf("------After Erase------\n");
	while (i < 4)
	{
		PrintPerson(PriQueuePeek(pqueue), &i);
		PriQueueDequeue(pqueue);
	}

	PriQueueDestroy(pqueue);

	/* TestDolev(); */
	TestMatan();
	return 0;
}
