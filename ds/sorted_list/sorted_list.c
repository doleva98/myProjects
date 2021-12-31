#include <stdio.h>

#include "sorted_list.h"
#include "doubly_linked_list.h"

struct SortedList
{
	is_before_func_t is_before;
	const void *equal_param;
	dlist_t *dlist;
};



/* Create new list */
sorted_list_t *SortedListCreate(is_before_func_t is_before, const void *param)
{
	sorted_list_t *list = NULL;
	list = (sorted_list_t*)calloc(1,sizeof(sorted_list_t));
	
	if(!list)
	{
		return NULL;
	}
	
	list->is_before = is_before;
	list->equal_param = param;
	list->dlist = DListCreate();
	if(!list->dlist)
	{
		free(list);
		return NULL;
	}
	return list;
}

/* Delete the list */
void SortedListDestroy(sorted_list_t *list)
{
	DListDestroy(list->dlist);
	free(list);
}


sorted_list_iter_t SortedListBegin(sorted_list_t *list)
{
	sorted_list_iter_t iter;
	iter.d_list_iter = DListBegin(list->dlist);
	iter.list = list;
	return iter;
}
sorted_list_iter_t SortedListEnd(sorted_list_t *list)
{
	sorted_list_iter_t iter;
	iter.d_list_iter = DListEnd(list->dlist);
	iter.list = list;
	return iter;
}
sorted_list_iter_t SortedListIterNext(sorted_list_iter_t iter)
{
	iter.d_list_iter = DListIterNext(iter.d_list_iter);	
	return iter;
}
sorted_list_iter_t SortedListIterPrev(sorted_list_iter_t iter)
{
	iter.d_list_iter = DListIterPrev(iter.d_list_iter);	
	return iter;
}
int SortedListIterIsEqual(sorted_list_iter_t iter1, sorted_list_iter_t iter2)
{
	return DListIterIsEqual(iter1.d_list_iter,iter2.d_list_iter);
}

void* SortedListIterGetData(sorted_list_iter_t iter)
{
	return DListIterGetData(iter.d_list_iter);
}


/* insert item to the list O(n) */
sorted_list_t *SortedListInsert(sorted_list_t *list, const void *item)
{
	sorted_list_iter_t iter = SortedListBegin(list);
	while(!SortedListIterIsEqual(iter, SortedListEnd(list)) && !list->is_before(item, SortedListIterGetData(iter), list->equal_param))
	{
		iter = SortedListIterNext(iter);
	}
	DListInsert(iter.d_list_iter, item);
	return list;
}


/* Remove item from the list */
void SortedListRemove(sorted_list_iter_t which)
{
	DListRemove(which.d_list_iter);
}

sorted_list_iter_t SortedListFind(sorted_list_iter_t from, sorted_list_iter_t to, const void *what)
{
	while(!SortedListIterIsEqual(from,to))
	{
		if(from.list->is_before(SortedListIterGetData(from), what, from.list->equal_param) && from.list->is_before(what, SortedListIterGetData(from), from.list->equal_param))
		{
			return from;
		}
		from = SortedListIterNext(from);
	}
	return SortedListEnd(from.list);
}

/*sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to, match_func_t is_match_func, void *param); */
int SortedListForEach(sorted_list_iter_t from, sorted_list_iter_t to, act_func_t action_func, void *param)
{
	return DListForEach(from.d_list_iter, to.d_list_iter, action_func, param);
}

size_t SortedListSize(sorted_list_t *list)
{
	return DListSize(list->dlist);
}

/* Merge lists */ 
sorted_list_t *SortListMerge(sorted_list_t *dest_list, sorted_list_t *src_list)
{
	sorted_list_iter_t iter = SortedListBegin(src_list);
	while(!SortedListIterIsEqual(iter, SortedListEnd(src_list)))
	{
		SortedListInsert(dest_list, SortedListIterGetData(iter));
		SortedListRemove(iter);
	}
	return dest_list;
}

sorted_list_iter_t SortedListFindIf(sorted_list_iter_t from, sorted_list_iter_t to, match_func_t is_match_func, void *param)
{
	while(!SortedListIterIsEqual(from, to))
	{
		if(is_match_func(SortedListIterGetData(from), param))
		{
			return from;
		}
		from = SortedListIterNext(from);
	}
	return SortedListEnd(from.list);
}











