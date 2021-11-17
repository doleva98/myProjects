#ifndef __SINGLY_LIST_H__
#define __SINGLY_LIST_H__

#include <stdlib.h>


typedef struct SList slist_t;
typedef struct SListNode snode_t;

typedef int (*action_func_t)(void *data, void *param);
typedef int (*match_func_t)(void *data, void *param);

typedef struct
{
	snode_t* node;
} slist_iter_t;


/* Create new list */
extern slist_t *SListCreate();

/* Delete the list */
extern void SListDestroy(slist_t *list);

extern slist_iter_t SListBegin(slist_t *list);
extern slist_iter_t SListEnd(slist_t *list);
extern slist_iter_t SListInsert(slist_iter_t iter, const void *item);
extern void SListRemove(slist_iter_t iter);
extern size_t SListCount(slist_t *list);

extern slist_iter_t SListIterNext(slist_iter_t iter);
extern int SListIterIsEqual(slist_iter_t iter1, slist_iter_t iter2);
extern void* SListIterGetData(slist_iter_t iter);

slist_iter_t SListFind(slist_iter_t from, slist_iter_t to, match_func_t is_match_func, void *param);
int SListForEach(slist_iter_t from, slist_iter_t to, action_func_t action_func, void *param);

  size_t SListCountForEach(slist_t *list);

#endif
