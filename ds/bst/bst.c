#include <stdio.h>
#include "bst.h"
#include <stdlib.h>
#include <assert.h>

static bst_iter_t FindMinInSubTree(bst_iter_t iter);
static bst_iter_t FindMaxInSubTree(bst_iter_t iter);
static int IsLeaf(bst_iter_t iter);
static bst_iter_t SetRoot(bst_iter_t iter);
static bst_node_t *CreatNode(const void *data);

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

	bst->root = CreatNode(NULL);
	bst->cmp_func = cmp_func;
	bst->param = param;

	return bst;
}

void BstDestroy(bst_t *bst)
{
}

size_t BstSize(bst_t *bst)
{
	size_t counter = 0;
	bst_iter_t iter;

	if (BstIsEmpty(bst))
	{
		return counter;
	}

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
	return bst->root == NULL;
}

bst_iter_t BstInsert(bst_t *bst, const void *data)
{
	/*if (!BstIterGetData(BstBegin(bst)))
	{
		bst_node_t *temp_node = bst->root;
		bst->root = CreatNode(data);
		bst->root->right_son = temp_node;
		return BstBegin(bst);
	}
	else
	{*/
	bst_iter_t iter = SetRoot(BstBegin(bst));
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
		else
		{
			break;
		}
	} /*end of while*/

	if (!BstIterGetData(iter))
	{
		bst_node_t *temp_node = iter.node;
		iter.node = CreatNode(data);
		iter.node->right_son = temp_node;
	}
	else if (iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param) < 0)
	{
		iter.node->left_son = CreatNode(data);
		iter.node->left_son->parent = iter.node;
	}
	else
	{
		iter.node->right_son = CreatNode(data);
		iter.node->right_son->parent = iter.node;
	}
	return iter;
	/*}*/
}

void BstRemove(bst_iter_t iter)
{
}

bst_iter_t BstBegin(bst_t *bst)
{
	bst_iter_t iter;
	iter.bst = bst;
	SetRoot(iter);
	return FindMinInSubTree(iter);
}

bst_iter_t BstEnd(bst_t *bst)
{
	bst_iter_t iter;
	iter.bst = bst;
	SetRoot(iter);
	return FindMaxInSubTree(iter);
}

bst_iter_t BstIterNext(bst_iter_t iter)
{
	const void *data = BstIterGetData(iter);
	if (iter.node->right_son)
	{
		iter.node = iter.node->right_son;
		return FindMinInSubTree(iter);
	}
	else /*right_son == NULL*/
	{
		bst_iter_t iter_res = SetRoot(iter);
		iter = SetRoot(iter);
		while (iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param))
		{
			if (iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param) < 0)
			{
				iter_res.node = iter.node;
				iter.node = iter.node->left_son;
			}
			else
			{
				iter.node = iter.node->right_son;
			}
		}
		return iter_res;
	}
}

bst_iter_t BstIterPrev(bst_iter_t iter)
{
	const void *data = BstIterGetData(iter);
	if (iter.node->left_son)
	{
		iter.node = iter.node->left_son;
		return FindMaxInSubTree(iter);
	}
	else /*left_son == NULL*/
	{
		bst_iter_t iter_res = SetRoot(iter);
		iter = SetRoot(iter);
		while (iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param))
		{
			if (iter.bst->cmp_func(data, BstIterGetData(iter), iter.bst->param) < 0)
			{
				iter.node = iter.node->left_son;
			}
			else
			{
				iter_res.node = iter.node;
				iter.node = iter.node->right_son;
			}
		}
		return iter_res;
	}
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
	while (!BstIterIsEqual(iter, BstEnd(bst)) && !bst->cmp_func(data, BstIterGetData(iter), bst->param))
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
	while (BstIterGetData(iter) && iter.node->left_son)
	{
		iter.node = iter.node->left_son;
	}
	return iter;
}

static bst_iter_t FindMaxInSubTree(bst_iter_t iter)
{
	while (BstIterGetData(iter) && iter.node->right_son)
	{
		iter.node = iter.node->right_son;
	}
	return iter;
}

static int IsLeaf(bst_iter_t iter)
{
	return !iter.node->left_son && !iter.node->right_son;
}

static bst_iter_t SetRoot(bst_iter_t iter)
{
	iter.node = iter.bst->root;
	return iter;
}

static bst_node_t *CreatNode(const void *data)
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