#include <stdio.h>
#include "priority_queue.h"
#include "string.h"

typedef struct
{
	int numId;
	char name[50];
}person_t;


static int IsLower(const void *new_elem, const void *curr_elem, const void *param);
static int match(const void *data, const void *param);

int main()
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
		
    	if(!(PriQueueSize(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(PriQueueIsEmpty(queue) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	PriQueueEnqueue(queue, &p3);/*3*/
	
	if(!(((person_t*)PriQueuePeek(queue))->numId == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	PriQueueEnqueue(queue, &p1);/*1,3*/
	
	if(!(((person_t*)PriQueuePeek(queue))->numId == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(PriQueueSize(queue) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	PriQueueDequeue(queue);/*1*/
	
	if(!(((person_t*)PriQueuePeek(queue))->numId == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(PriQueueSize(queue) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(PriQueueIsEmpty(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(strcmp(((person_t*)PriQueuePeek(queue))->name,"Dumbeldore") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	PriQueueEnqueue(queue, &p4);
	PriQueueEnqueue(queue, &p2);/*1,2,4*/
	
	if(!(((person_t*)PriQueuePeek(queue))->numId == 8))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(strcmp(((person_t*)PriQueuePeek(queue))->name,"Hermione Granger") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(PriQueueSize(queue) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	test = 2;
	
	PriQueueErase(queue, match, &test);/*1,4*/
	
	if(!(PriQueueSize(queue) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	test = 8;
	
	PriQueueErase(queue, match, &test);/*1*/
	
	if(!(((person_t*)PriQueuePeek(queue))->numId == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(strcmp(((person_t*)PriQueuePeek(queue))->name,"Dumbeldore") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	PriQueueEnqueue(queue, &p2);
	PriQueueEnqueue(queue, &p3);
	PriQueueEnqueue(queue, &p4);
	
	if(!(strcmp(((person_t*)PriQueuePeek(queue))->name,"Hermione Granger") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(PriQueueSize(queue) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	PriQueueClear(queue);
	
	if(!(PriQueueSize(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(PriQueueIsEmpty(queue) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	PriQueueEnqueue(queue, &p2);
	PriQueueEnqueue(queue, &p3);

	if(!(PriQueueSize(queue) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	if(!(strcmp(((person_t*)PriQueuePeek(queue))->name,"Ronald Wiseley") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(PriQueueIsEmpty(queue) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	PriQueueDestroy(queue);
	return 0;
}

static int IsLower(const void *new_elem, const void *curr_elem, const void *param)
{
	int num1, num2, IsLowToHigh;
	if(!curr_elem)
	{
		return 1;
	}
	num1 = ((person_t*)new_elem)->numId;
	num2 = ((person_t*)curr_elem)->numId;
	IsLowToHigh = *(int*)param;
	if(IsLowToHigh)
	{
		return num1 <= num2;
	}
	else
	{
		return num2 <= num1;
	}

}

static int match(const void *data, const void *param)
{
	int num1, num2;
	
	num1 = ((person_t*)data)->numId;
	num2 = *(int*)param;
	return num1 == num2;
}
