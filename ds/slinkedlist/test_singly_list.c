#include <stdio.h>
#include <string.h>
#include "singly_list.h"


typedef struct 
{
    size_t idNum;
} person_t;


static int IsMatch(void* data, void* param)
{
    person_t* p = (person_t*)data;

    if (p->idNum == *(size_t*)param)
    {
        return 1;
    }

    return 0;
}


static int print(void* data, void* param)
{

	(void)param;
	printf("%lu\n", *(size_t*)data);
	return 1;
}

static int Minus(void* data, void* param)
{

	*(size_t*)data = *(size_t*)data - *(size_t*)param;
	return 1;
}

int main() {

    slist_t *list = SListCreate();
    
	slist_iter_t iter = SListBegin(list);
	slist_iter_t iter2 = SListBegin(list);
	slist_iter_t iter3 = SListBegin(list);
	int a = 5;
	char b [15] = "Dumbeldore";
	int c = 100;
	
	size_t test1;
	person_t p1, p2, p3;
    	slist_iter_t iter4, iter5;
	slist_t* list2;
	
	if(!(SListIterIsEqual(iter, iter2) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
		
	
	
    	if(!(SListCount(list) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListInsert(iter, &a);
	
	if(!(SListCount(list) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(*(int*)SListIterGetData(iter) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	iter = SListIterNext(iter);
	SListInsert(iter, b); /*a, b */
	
	if(!(SListCount(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(strcmp((char*)SListIterGetData(iter),"Dumbeldore" ) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListInsert(iter, &c);/*a, c, b*/
	
	if(!(SListCount(list) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	

	if(!(*(int*)SListIterGetData(iter) == 100))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	iter = SListIterNext(iter);
	
	if(!(strcmp((char*)SListIterGetData(iter),"Dumbeldore" ) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	iter2 = SListIterNext(iter2);
	SListRemove(iter2);/*a, b*/
	
	if(!(SListCount(list) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}

	if(!(strcmp((char*)SListIterGetData(iter2),"Dumbeldore" ) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	SListRemove(iter3);/*b*/
	
	if(!(strcmp((char*)SListIterGetData(iter3),"Dumbeldore" ) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(SListCount(list) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}


	SListDestroy(list);
	
	
	/****************************************************/
	
	p1.idNum = 111;
	p2.idNum = 445;
	p3.idNum = 123;
	
	list2 = SListCreate();
	
	SListInsert(SListEnd(list2), &p1);
    	SListInsert(SListEnd(list2), &p2);
    	SListInsert(SListEnd(list2), &p3);
    	
    	if(!(SListCount(list2) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
    	
	iter4 = SListBegin(list2);
	iter5 = SListIterNext(iter4);
	iter5 = SListIterNext(iter5);
	

	
	test1 = 445;
	
	iter4 = SListFind(SListBegin(list2), iter5, IsMatch, &test1);
	

	
	if(!(((person_t*)SListIterGetData(iter4))->idNum == 445))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	test1 = 123;
	iter4 = SListFind(SListBegin(list2), SListEnd(list2), IsMatch, &test1);
	
	if(!(((person_t*)SListIterGetData(iter4))->idNum == 123))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListForEach(SListBegin(list2), SListEnd(list2), print, NULL);
	
	puts(" ");
	test1 = 20;
	SListForEach(SListBegin(list2), SListEnd(list2), Minus, &test1);
	
	SListForEach(SListBegin(list2), SListEnd(list2), print, NULL);
	
	if(!(SListCountForEach(list2) == 3))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListDestroy(list2);
	
   return 0;
}

