#include <stdio.h>
#include <assert.h>
#include "singly_list.h"

static int PlusOne(void* data, void* param);

struct SList
{
	snode_t *head;
	slist_iter_t *IterHead;
};

struct SListNode
{
	const void *data;
	snode_t *next;
};

/* Create new list */
 slist_t *SListCreate()
{
	
	slist_t *list = NULL;
	list = (slist_t*)calloc(1,sizeof(slist_t));
	
	if(!list)
	{
		return NULL;
	}	
	
	list->head = (snode_t*)calloc(1,sizeof(snode_t));/*dummy*/
	if(!list->head)
	{
		return NULL;
	}
	
	list->head->data = NULL;
	list->head->next = NULL;
	
	list->IterHead = (slist_iter_t*)calloc(1,sizeof(slist_iter_t));
	if(!list->IterHead)
	{
		return NULL;
	}
	list->IterHead->node = list->head;
	return list;
}

/* Delete the list */

 void SListDestroy(slist_t *list)
 {
 	 slist_iter_t iter = SListBegin(list);
 	assert(list);

 	
	while(iter.node->next)
	{
		SListRemove(iter);
	}
	
	free(list->head);
	list->head = NULL;
 	free(list->IterHead);
 	list->IterHead = NULL;
 	free(list);
 }

 slist_iter_t SListBegin(slist_t *list)
 {
 	 assert(list);
 	return *list->IterHead;
 }
 
 slist_iter_t SListEnd(slist_t *list)
 {	
 	slist_iter_t iter = SListBegin(list);
 	assert(list);
	for(;iter.node->next != NULL; iter = SListIterNext(iter))
	{
	}
	return iter;
 }
 
 slist_iter_t SListInsert(slist_iter_t iter, const void *item)
 {	
 	snode_t *temp = NULL; 
 	assert(iter.node);
 	temp = (snode_t*)calloc(1,sizeof(snode_t));
	if(!temp)
	{
		return iter;
	}
	temp->data = iter.node->data; 
	temp->next = iter.node->next;
	iter.node->next = temp;
	iter.node->data = item;
	return iter;
 }
 
 void SListRemove(slist_iter_t iter)
 {	
 	snode_t *temp = iter.node->next;
 	assert(iter.node);
 	if(NULL == iter.node->next)
    	{
        	return;
    	}
 	iter.node->data = iter.node->next->data;
 	iter.node->next = iter.node->next->next;
 	
 	free(temp);
 }
 
 size_t SListCount(slist_t *list)
 {
 	size_t count = 0; /*counts the dummmy head*/ 	
 	slist_iter_t iter = SListBegin(list);
 	
 	assert(list);
 	
	for(;!SListIterIsEqual(iter, SListEnd(list)); iter = SListIterNext(iter))
	{
		++count;
	}
	
 	return count;
 }

 slist_iter_t SListIterNext(slist_iter_t iter)
 {
 	assert(iter.node);
 	iter.node = iter.node->next;
 	return iter;
 }
 
 int SListIterIsEqual(slist_iter_t iter1, slist_iter_t iter2)
 {
 	return iter1.node == iter2.node;
 }
 
 void* SListIterGetData(slist_iter_t iter)
 {
 	assert(iter.node);
 	return (void*)iter.node->data;
 }
 
 
slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t is_match_func, void *param)
{
	
	for(;!SListIterIsEqual(from, to); from = SListIterNext(from))
	{
		if(is_match_func((void*)from.node->data, param))
		{
			return from;
		}
	}	
	return from;
}

int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param)
{

	for(;!SListIterIsEqual(from, to); from = SListIterNext(from))
	{
		if(!action_func((void*)from.node->data, param))
		{
			return 0;
		}
	}
	return 1;
}
 
  size_t SListCountForEach(slist_t *list)
  {
  	size_t count = 0;
  	
	SListForEach(SListBegin(list), SListEnd(list), PlusOne, &count);
	return count;
  }
 
static int PlusOne(void* data, void* param)
{
	(void)data;
	++*(size_t*)param;
	return 1;
}

 
 
 
 
 

