#include <stdio.h>
#include "bst.h"
#include <stdlib.h>
#include <assert.h>

static bst_iter_t FindMinInSubTree(bst_iter_t iter);
static bst_iter_t FindMaxInSubTree(bst_iter_t iter);
static int IsLeaf(bst_iter_t iter);
static bst_node_t *CreateNode(const void *data);
static int hasOneChild(bst_iter_t iter);
static void FindAndLinkParentToSon(bst_iter_t iter, bst_node_t *node_to_change);
static bst_iter_t SetRoot(bst_t *bst);

struct BST
{
	bst_node_t *root;
	compare_func_t cmp_func;
	const void *param;
};

struct BSTNode
{
	const void *data;
	bst_node_t *right_son;
	bst_node_t *left_son;
	bst_node_t *parent;
};

bst_t *BstCreate(compare_func_t cmp_func, const void *param)
{
	bst_t *bst = NULL;

	bst = (bst_t *)malloc(sizeof(bst_t));
	if (!bst)
	{
		return NULL;
	}

	bst->root = CreateNode(NULL);
	if (!bst->root)
	{
		free(bst);
		return NULL;
	}
	bst->cmp_func = cmp_func;
	bst->param = param;

	return bst;
}

void BstDestroy(bst_t *bst)
{
	while (bst->root != BstEnd(bst).node)
	{
		BstRemove(BstBegin(bst));
	}
	free(bst->root);
	free(bst);
}

size_t BstSize(bst_t *bst)
{
	size_t counter = 0;
	bst_iter_t iter;

	iter = BstBegin(bst);
	while (!BstIterIsEqual(iter, BstEnd(bst)))
	{
		++counter;
		iter = BstIterNext(iter);
	}
	return counter;
}

int BstIsEmpty(bst_t *bst)
{
	return !BstEnd(bst).node->parent;
}

bst_iter_t BstInsert(bst_t *bst, const void *data)
{
	if (!BstIterGetData(BstBegin(bst))) /*dummy is in the root*/
	{
		bst_node_t *temp_node = bst->root;
		bst->root = CreateNode(data);
		bst->root->right_son = temp_node;
		temp_node->parent = bst->root;
		return BstBegin(bst);
	}
	else
	{
		bst_iter_t iter;
		iter.node = bst->root;
		iter.bst = bst;
		while (!IsLeaf(iter))
		{

			assert(iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param));

			if (iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param) < 0 && iter.node->left_son)
			{
				iter.node = iter.node->left_son;
			}
			else if (iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param) > 0 && iter.node->right_son)
			{
				iter.node = iter.node->right_son;
			}
			else /*has one child, and i want to add to the NULL child*/
			{
				break;
			}
		} /*end of while*/

		if (!BstIterGetData(iter))
		{

			bst_node_t *temp_node = iter.node;

			iter.node = CreateNode(data);

			iter.node->right_son = temp_node;
			iter.node->parent = temp_node->parent;
			temp_node->parent->right_son = iter.node;
			temp_node->parent = iter.node;
		}
		else if (iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param) < 0)
		{
			iter.node->left_son = CreateNode(data);
			iter.node->left_son->parent = iter.node;
		}
		else
		{
			iter.node->right_son = CreateNode(data);
			iter.node->right_son->parent = iter.node;
		}
		return iter;
	}
}

void BstRemove(bst_iter_t iter)
{
	if (!BstIterGetData(iter))
	{
		return;
	}
	else if (IsLeaf(iter))
	{
		if (iter.node->parent->left_son == iter.node)
		{
			iter.node->parent->left_son = NULL;
		}
		else
		{
			iter.node->parent->right_son = NULL;
		}
		free(iter.node);
	}
	else if (hasOneChild(iter))
	{
		if (iter.node->right_son) /*has right child*/
		{
			FindAndLinkParentToSon(iter, iter.node->right_son);
		}
		else /*has left child*/
		{
			FindAndLinkParentToSon(iter, iter.node->right_son);
		}
		free(iter.node);
	}
	else /*2 child*/
	{
		if ((BstIterIsEqual(iter, BstIterPrev(BstEnd(iter.bst)))))
		{
			bst_iter_t prev_iter = BstIterPrev(iter);
			iter.node->data = BstIterGetData(prev_iter);
			if (prev_iter.node->left_son)
			{
				prev_iter.node->left_son->parent = prev_iter.node->parent;
				prev_iter.node->parent->right_son = prev_iter.node->left_son;
			}
			free(prev_iter.node);
		}
		else
		{
			bst_iter_t next_iter = BstIterNext(iter);
			iter.node->data = BstIterGetData(next_iter);
			if (next_iter.node->right_son)
			{
				next_iter.node->right_son->parent = next_iter.node->parent;
				next_iter.node->parent->left_son = next_iter.node->right_son;
			}
			free(next_iter.node);
		}
	}
}

bst_iter_t BstBegin(bst_t *bst)
{
	return FindMinInSubTree(SetRoot(bst));
}

bst_iter_t BstEnd(bst_t *bst)
{
	return FindMaxInSubTree(SetRoot(bst));
}

bst_iter_t BstIterNext(bst_iter_t iter)
{
	const void *data = BstIterGetData(iter);
	if (iter.node->right_son)
	{
		iter.node = iter.node->right_son;
		iter = FindMinInSubTree(iter);
	}
	else /*right_son == NULL*/
	{
		do
		{
			iter.node = iter.node->parent;
		} while (iter.node != iter.bst->root && iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param) > 0);
	}
	return iter;
}

bst_iter_t BstIterPrev(bst_iter_t iter)
{
	const void *data = BstIterGetData(iter);
	if (!data)
	{
		iter.node = iter.node->parent;
	}
	else if (iter.node->left_son)
	{
		iter.node = iter.node->left_son;
		iter = FindMaxInSubTree(iter);
	}
	else /*left_son == NULL*/
	{
		do
		{
			iter.node = iter.node->parent;
		} while (iter.node != iter.bst->root && iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param) < 0);
	}
	return iter;
}

int BstIterIsEqual(bst_iter_t iter1, bst_iter_t iter2)
{
	return iter1.node == iter2.node;
}

const void *BstIterGetData(bst_iter_t iter)
{
	return iter.node->data;
}

bst_iter_t BstFind(bst_t *bst, const void *data)
{
	bst_iter_t iter = BstBegin(bst);
	while (!BstIterIsEqual(iter, BstEnd(bst)) && bst->cmp_func(data, BstIterGetData(iter), bst->param))
	{
		iter = BstIterNext(iter);
	}
	return iter;
}

int BstForEach(bst_iter_t from, bst_iter_t to, action_func_t action_func, const void *param)
{
	while (!BstIterIsEqual(from, to))
	{
		if (!action_func((void *)BstIterGetData(from), param))
		{
			return 0;
		}
		from = BstIterNext(from);
	}
	return 1;
}

static bst_iter_t FindMinInSubTree(bst_iter_t iter)
{
	while (iter.node->left_son)
	{
		iter.node = iter.node->left_son;
	}
	return iter;
}

static bst_iter_t FindMaxInSubTree(bst_iter_t iter)
{
	while (iter.node->right_son)
	{
		iter.node = iter.node->right_son;
	}
	return iter;
}

static int IsLeaf(bst_iter_t iter)
{
	return !iter.node->left_son && !iter.node->right_son;
}

static int hasOneChild(bst_iter_t iter)
{
	return (iter.node->right_son && !iter.node->left_son) || (!iter.node->right_son && iter.node->left_son);
}

static bst_node_t *CreateNode(const void *data)
{
	bst_node_t *node = NULL;

	node = (bst_node_t *)malloc(sizeof(bst_node_t));
	if (!node)
	{
		return NULL;
	}

	node->data = data;
	node->left_son = NULL;
	node->right_son = NULL;
	node->parent = NULL;
	return node;
}

static void FindAndLinkParentToSon(bst_iter_t iter, bst_node_t *node_to_change)
{
	if (iter.bst->root == iter.node)
	{
		iter.bst->root = node_to_change;
	}
	else if (iter.node->parent->left_son == iter.node)
	{
		iter.node->parent->left_son = node_to_change;
	}
	else
	{
		iter.node->parent->right_son = node_to_change;
	}
	node_to_change->parent = iter.node->parent;
}

static bst_iter_t SetRoot(bst_t *bst)
{
	bst_iter_t iter;
	iter.bst = bst;
	iter.node = bst->root;
	return iter;
}