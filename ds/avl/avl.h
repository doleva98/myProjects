#ifndef __AVL_H__
#define __AVL_H__

#include <stddef.h>

typedef int (*compare_func_t)(const void *new_elem, const void *curr_elem, const void *param); /*1 if new elem < curr*/
typedef int (*action_func_t)(const void *data, const void *param);                             /* SUCCESS = 0, FAIL = 1*/

typedef enum Traversal
{
    IN_ORDER,
    PRE_ORDER,
    POST_ORDER
} traversal_t;

typedef struct AVL avl_t;

/* Create new AVL*/
avl_t *AvlCreate(compare_func_t cmp_func, const void *param);

/* Destroy AVL*/
void AvlDestroy(avl_t *avl);

/* Size of AVL*/
size_t AvlSize(const avl_t *avl);

/* Height of root */
size_t AvlHeight(const avl_t *avl);

/* If AVL is Empty return 1  */
int AvlIsEmpty(const avl_t *avl);

/* Insert a new node - 0 if success, 1 fail */
int AvlInsert(avl_t *avl, const void *data);

/* Remove a node  */
void AvlRemove(avl_t *avl, const void *data);

/* Find a node in AVL  */
const void *AvlFind(avl_t *avl, const void *data);

int AvlForEach(avl_t *avl, action_func_t action_func, const void *param, traversal_t order);

void nAvlRemove(avl_t *avl, const void *data);
#endif