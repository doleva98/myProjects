/*
output:

----------------GOOD GUYS-----------------
Dumbeldore is number 1
Harry Potter is number 2
Ronald Wiseley is number 3
Hermione Granger is number 8
-------------HAGRID COMES----------------
Dumbeldore is a wizard is number 1
Harry Potter is a wizard is number 2
Ronald Wiseley is a wizard is number 3
Hermione Granger is a wizard is number 8
---------------BAD GUYS-----------------
a The Death Eater is number 0
Peter Pettigrew is number 2
Lord Voldemort is number 5
Dolores Umbridge is number 7
---------------FINAL BATTLE-----------------
a The Death Eater is number 0
Dumbeldore is a wizard is number 1
Peter Pettigrew is number 2
Harry Potter is a wizard is number 2
Ronald Wiseley is a wizard is number 3
Lord Voldemort is number 5
Dolores Umbridge is number 7
Hermione Granger is a wizard is number 8

*/

#include <stdio.h>
#include "sorted_list.h"
#include "string.h"
typedef struct
{
	int numId;
	char name[50];
}person_t;

static int IsLower(const void *new_elem, const void *curr_elem, const void *param);
static int print(void *data, void *param);
static int catAString(void *data, void *param);
static int match(void *data, void *param);
int main()
{
	int IsUpParam = 1;
	sorted_list_t *list = SortedListCreate(IsLower, &IsUpParam);
	sorted_list_iter_t iter = SortedListBegin(list);
	person_t p1;	
	person_t p2;	
	person_t p3;	
	person_t p4;	
	person_t p5;
	int wow;
	person_t p6;
	person_t p7;
	person_t p8;
	person_t p9;
	int test;
	sorted_list_t *list2;	
    	if(!(SortedListSize(list) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	p1.numId = 1;
	strcpy(p1.name, "Dumbeldore");

	p5.numId = 1;
	strcpy(p5.name, "Dumbeldore");
	
	p2.numId = 2;
	strcpy(p2.name, "Harry Potter");
	
	p3.numId = 3;
	strcpy(p3.name, "Ronald Wiseley");
	
	p4.numId = 8;
	strcpy(p4.name, "Hermione Granger");
	
	SortedListInsert(list, &p4);
	
	if(!(SortedListSize(list) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(((person_t*)SortedListIterGetData(iter))->numId == 8))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SortedListInsert(list, &p1);/*p1,p4*/
	
	if(!(SortedListSize(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(((person_t*)SortedListIterGetData(iter))->numId == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	iter = SortedListIterNext(iter);
	
	if(!(((person_t*)SortedListIterGetData(iter))->numId == 8))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SortedListInsert(list, &p3);/*p1,p3,p4*/
	
	if(!(((person_t*)SortedListIterGetData(iter))->numId == 3))
	{
		printf("fail in %d\n", __LINE__);
	}

	if(!(strcmp(((person_t*)SortedListIterGetData(iter))->name, "Ronald Wiseley") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	SortedListInsert(list, &p2);
	SortedListInsert(list, &p5);/*p1,p5,p2,p3,p4*/	
	
	if(!(((person_t*)SortedListIterGetData(iter))->numId == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	if(!(strcmp(((person_t*)SortedListIterGetData(iter))->name, "Harry Potter") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(SortedListSize(list) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	iter = SortedListIterPrev(iter);/*at p5*/
	SortedListRemove(iter);/*p1,p2,p3,p4*/
	
	if(!(((person_t*)SortedListIterGetData(iter))->numId == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	if(!(strcmp(((person_t*)SortedListIterGetData(iter))->name, "Harry Potter") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(SortedListSize(list) == 4))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(strcmp(((person_t*)SortedListIterGetData(SortedListIterPrev(SortedListEnd(list))))->name, "Hermione Granger") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	
	iter = SortedListBegin(list);
	test = 3;
	iter = SortedListFind(iter, SortedListEnd(list), &test);
	
	if(!(((person_t*)SortedListIterGetData(iter))->numId == 3))
	{
		printf("fail in %d\n", __LINE__);
	}

	if(!(strcmp(((person_t*)SortedListIterGetData(iter))->name, "Ronald Wiseley") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	test = 30;
	iter = SortedListFind(iter, SortedListEnd(list), &test);
	
	if(!(SortedListIterIsEqual(iter,SortedListEnd(list))))
	{
		printf("fail in %d\n", __LINE__);
	}
	puts("----------------GOOD GUYS-----------------");
	SortedListForEach(SortedListBegin(list), SortedListEnd(list), print, NULL);
	puts("-------------HAGRID COMES----------------");
	SortedListForEach(SortedListBegin(list), SortedListEnd(list), catAString, " is a wizard");
	SortedListForEach(SortedListBegin(list), SortedListEnd(list), print, NULL);
	
	puts("---------------BAD GUYS-----------------");
		
	p6.numId = 5;
	strcpy(p6.name, "Lord Voldemort");

	p7.numId = 7;
	strcpy(p7.name, "Dolores Umbridge");
	
	p8.numId = 2;
	strcpy(p8.name, "Peter Pettigrew");
	
	p9.numId = 0;
	strcpy(p9.name, "a The Death Eater");
	
	list2 = SortedListCreate(IsLower, &IsUpParam);
	
	SortedListInsert(list2, &p6);
	SortedListInsert(list2, &p7);
	SortedListInsert(list2, &p8);	
	SortedListInsert(list2, &p9);
	SortedListForEach(SortedListBegin(list2), SortedListEnd(list2), print, NULL);	
	puts("---------------FINAL BATTLE-----------------");
	SortListMerge(list, list2);
	SortedListForEach(SortedListBegin(list2), SortedListEnd(list2), print, NULL);	/*should print nothing*/
	if(!(SortedListSize(list2) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(SortedListSize(list) == 8))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(SortedListIterIsEqual(SortedListBegin(list2), SortedListEnd(list2)) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SortedListForEach(SortedListBegin(list), SortedListEnd(list), print, NULL);
	wow = 3;
	
	if(!(strcmp(((person_t*)SortedListIterGetData(SortedListFindIf(SortedListBegin(list), SortedListEnd(list), match, &wow)))->name, "Ronald Wiseley is a wizard") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SortedListDestroy(list);
	SortedListDestroy(list2);
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

static int print(void *data, void *param)
{
	(void)param;
	printf("%s is number %d\n", ((person_t*)data)->name, ((person_t*)data)->numId);
	return 1;
}

static int catAString(void *data, void *param)
{
	strcat(((person_t*)data)->name, (char*)param);
	return 1;
}

static int match(void *data, void *param)
{
	int num1, num2;
	
	num1 = ((person_t*)data)->numId;
	num2 = *(int*)param;
	return num1 == num2;
}



