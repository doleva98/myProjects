#include <stdio.h>
#include <assert.h>
#include "singly_list.h"

struct SList
{
	snode_t *head;
	slist_iter_t *IterHead;
};

struct SListNode
{
	void *data;
	snode_t *next;
};

/* Create new list */
 slist_t *SListCreate()
{
	
	slist_t *list = (slist_t*)calloc(1,sizeof(slist_t));
	
	if(!list)
	{
		return NULL;
	}	
	
	list->head = (snode_t*)calloc(1,sizeof(snode_t));
	if(!list->head)
	{
		return NULL;
	}
	
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
 	list = NULL;
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
 
 void SListInsert(slist_iter_t iter, void *item)
 {	
 	snode_t *temp = NULL; 
 	assert(iter.node);
 	temp = (snode_t*)calloc(1,sizeof(snode_t));
	if(!temp)
	{
		return;
	}
	temp->data = item; 
	temp->next = iter.node->next;
	iter.node->next = temp;
 }
 
 void SListRemove(slist_iter_t iter)
 {
 	snode_t *temp = iter.node->next->next;
 	assert(iter.node);
 	free(iter.node->next);
 	iter.node->next = temp;
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
 	assert(iter.node->next);
 	return iter.node->next->data;
 }
 
 
 
 
 
 
 
 
 
 
 
 
