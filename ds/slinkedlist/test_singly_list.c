#include <stdio.h>
#include <string.h>
#include "singly_list.h"

int main() {

    slist_t *list = SListCreate();
    
	slist_iter_t iter = SListBegin(list);
	slist_iter_t iter2 = SListBegin(list);
	slist_iter_t iter3 = SListBegin(list);
	int a = 5;
	char b [15] = "Dumbeldore";
	int c = 100;
	
	
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

	if(!(*(int*)SListIterGetData(iter2) == 100))
	{
		printf("fail in %d\n", __LINE__);
	}
	SListRemove(iter3);/*a*/
	
	if(!(*(int*)SListIterGetData(iter3) == 5))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(SListCount(list) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	SListDestroy(list);
	
	
   return 0;
}
