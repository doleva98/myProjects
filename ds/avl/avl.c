#include <stdio.h>
#include "avl.h"
#include <stdlib.h>

typedef struct AvlNode avl_node_t;

struct AvlNode
{
	const void *data;
	avl_node_t *right_son;
	avl_node_t *left_son;
	size_t height;
};

struct AVL
{
	avl_node_t *root;
	compare_func_t cmp_func;
	const void *param;
};

static avl_node_t *CreateNode(const void *data);
static void AvlDestroyHelper(avl_node_t *node);
static int AvlInsertHelper(avl_t *avl, avl_node_t *node, const void *data);
static size_t max(size_t height1, size_t height2);
static size_t getHeight(avl_node_t *node);

static int AvlForEachHelper(avl_t *avl, avl_node_t *node, action_func_t action_func, const void *param, traversal_t order);
static int Count(const void *data, const void *param);
static const void *AvlFindHelper(avl_t *avl, avl_node_t *node, const void *data);

static int HasOneChild(avl_node_t *node);
static avl_node_t *FindNextAndRemoveInRightSubTree(avl_node_t *node);
/*static avl_node_t *FindPrevAndRemoveInLeftSubTree(avl_node_t *node);*/
static void AvlRemoveHelper(avl_t *avl, avl_node_t *node, const void *data);

avl_t *AvlCreate(compare_func_t cmp_func, const void *param)
{
	avl_t *avl = NULL;

	avl = (avl_t *)malloc(sizeof(avl_t));
	if (!avl)
	{
		return NULL;
	}

	avl->root = NULL;
	avl->cmp_func = cmp_func;
	avl->param = param;

	return avl;
}

/* Destroy AVL*/
void AvlDestroy(avl_t *avl)
{
	AvlDestroyHelper(avl->root);
	free(avl);
}

/* Size of AVL*/
size_t AvlSize(const avl_t *avl)
{
	size_t size = 0;
	AvlForEach((avl_t *)avl, Count, &size, IN_ORDER);
	return size;
}

/* Height of root */
size_t AvlHeight(const avl_t *avl)
{
	return getHeight(avl->root);
}

/* If AVL is Empty return 1  */
int AvlIsEmpty(const avl_t *avl)
{
	return !avl->root;
}

/* Insert a new node - 0 if success, 1 fail */
int AvlInsert(avl_t *avl, const void *data)
{
	if (!avl->root)
	{
		avl->root = CreateNode(data);
		return !!avl->root;
	}
	return AvlInsertHelper(avl, avl->root, data);
}

/* Remove a node  */
void AvlRemove(avl_t *avl, const void *data)
{
	avl_node_t *curr = avl->root;
	if (!curr)
	{
		return;
	}
	else if (avl->cmp_func(data, avl->root->data, avl->param) == 0)
	{
		if (getHeight(avl->root) == 1)
		{
			avl->root = NULL;
		}
		else if (HasOneChild(avl->root))
		{
			if (avl->root->right_son)
			{
				avl->root = avl->root->right_son;
			}
			else /*has left child*/
			{
				avl->root = avl->root->left_son;
			}
		}
		else /*root has two sons*/
		{
			if (avl->root->right_son->left_son)
			{
				avl->root = FindNextAndRemoveInRightSubTree(avl->root->right_son);
				avl->root->right_son = curr->right_son;
			}
			else
			{
				avl->root = avl->root->right_son;
			}
			avl->root->left_son = curr->left_son;
		}
		free(curr);
		avl->root->height = 1 + max(getHeight(avl->root->left_son), getHeight(avl->root->right_son));
	}
	else
	{
		AvlRemoveHelper(avl, avl->root, data);
	}
}

/* Find a node in AVL  */
const void *AvlFind(avl_t *avl, const void *data)
{
	if (!avl->root)
	{
		return NULL;
	}
	return AvlFindHelper(avl, avl->root, data);
}

int AvlForEach(avl_t *avl, action_func_t action_func, const void *param, traversal_t order)
{
	if (!avl->root)
	{
		return 0;
	}
	return AvlForEachHelper(avl, avl->root, action_func, param, order);
}

/***********************************for node**********************************************/
static avl_node_t *CreateNode(const void *data)
{
	avl_node_t *node = NULL;

	node = (avl_node_t *)malloc(sizeof(avl_node_t));
	if (!node)
	{
		return NULL;
	}

	node->data = data;
	node->left_son = NULL;
	node->right_son = NULL;
	node->height = 1;

	return node;
}

/***************helpers for recursion*********/
static int AvlInsertHelper(avl_t *avl, avl_node_t *node, const void *data)
{
	int result = 1;
	if (avl->cmp_func(data, node->data, avl->param) < 0) /*needs to go to the left*/
	{
		if (node->left_son)
		{
			result = AvlInsertHelper(avl, node->left_son, data);
		}
		else
		{
			node->left_son = CreateNode(data);
			result = !!node->left_son;
		}
	}
	else /*needs to go to the right*/
	{
		if (node->right_son)
		{
			result = AvlInsertHelper(avl, node->right_son, data);
		}
		else
		{
			node->right_son = CreateNode(data);
			result = !!node->right_son;
		}
	}
	node->height = 1 + max(getHeight(node->left_son), getHeight(node->right_son));

	return result;
}

static size_t getHeight(avl_node_t *node)
{
	if (!node)
	{
		return 0;
	}
	return node->height;
}

static size_t max(size_t height1, size_t height2)
{
	return height1 > height2 ? height1 : height2;
}

/**************helper functions for foreach******/

static int AvlForEachHelper(avl_t *avl, avl_node_t *node, action_func_t action_func, const void *param, traversal_t order)
{
	int result = 1;
	if (getHeight(node) == 0)
	{
		return 0;
	}

	else if (order == PRE_ORDER)
	{
		action_func(node->data, param);
		result = AvlForEachHelper(avl, node->left_son, action_func, param, order);
		if (result == 1)
		{
			return 1;
		}
		result = AvlForEachHelper(avl, node->right_son, action_func, param, order);
		return result;
	}
	else if (order == IN_ORDER)
	{
		result = AvlForEachHelper(avl, node->left_son, action_func, param, order);
		if (result == 1)
		{
			return 1;
		}
		action_func(node->data, param);
		result = AvlForEachHelper(avl, node->right_son, action_func, param, order);
		return result;
	}
	else /*Post order*/
	{
		result = AvlForEachHelper(avl, node->left_son, action_func, param, order);
		if (result == 1)
		{
			return 1;
		}
		result = AvlForEachHelper(avl, node->right_son, action_func, param, order);
		action_func(node->data, param);
		return result;
	}
}

/***************for size*******/

static int Count(const void *data, const void *param)
{
	(void)data;
	++*(size_t *)param;
	return 0;
}

/***********for find**************/

static const void *AvlFindHelper(avl_t *avl, avl_node_t *node, const void *data)
{
	if (!node)
	{
		return NULL;
	}
	if (avl->cmp_func(data, node->data, avl->param) == avl->cmp_func(node->data, data, avl->param))
	{
		return node->data;
	}
	if (avl->cmp_func(data, node->data, avl->param) < 0) /*go to the left*/
	{
		return AvlFindHelper(avl, node->left_son, data);
	}
	else /*go to the right*/
	{
		return AvlFindHelper(avl, node->right_son, data);
	}
}

/****************remove**************/

static avl_node_t *FindNextAndRemoveInRightSubTree(avl_node_t *node)
{
	if (node->left_son)
	{
		if (!node->left_son->left_son)
		{
			avl_node_t *temp = node->left_son;
			node->left_son = node->left_son->right_son;
			return temp;
		}
		return FindNextAndRemoveInRightSubTree(node->left_son);
	}
	return NULL;
}
/*
static avl_node_t *FindPrevAndRemoveInLeftSubTree(avl_node_t *node)
{
	if (node->right_son)
	{
		if (!node->right_son->right_son)
		{
			avl_node_t *temp = node->right_son;
			node->right_son = node->right_son->left_son;
			return temp;
		}
		return FindNextAndRemoveInRightSubTree(node->right_son);
	}
	return NULL;
}*/

static int HasOneChild(avl_node_t *node)
{
	return (node->right_son && !node->left_son) || (!node->right_son && node->left_son);
}

static void AvlRemoveHelper(avl_t *avl, avl_node_t *node, const void *data)
{
	avl_node_t *curr = NULL;
	if (avl->cmp_func(data, node->data, avl->param) < 0) /*go to the left*/
	{
		curr = node->left_son;
		if (curr && avl->cmp_func(data, curr->data, avl->param) == 0)
		{
			if (getHeight(curr) == 1)
			{
				node->left_son = NULL;
				free(curr);
			}
			else if (HasOneChild(curr))
			{
				if (curr->left_son)
				{
					node->left_son = curr->left_son;
				}
				else
				{
					node->left_son = curr->right_son;
				}
				free(curr);
			}
			else /*node has 2 children*/
			{
				if (curr->right_son->left_son)
				{
					node->left_son = FindNextAndRemoveInRightSubTree(curr->right_son);
					node->left_son->right_son = curr->right_son;
				}
				else
				{
					node->left_son = curr->right_son;
				}
				node->left_son->left_son = curr->left_son;
				free(curr);
				node->right_son->height = 1 + max(getHeight(node->left_son->left_son), getHeight(node->left_son->right_son));
				return;
			}
		}
		else
		{
			AvlRemoveHelper(avl, node->left_son, data);
		}
	}
	else if (avl->cmp_func(data, node->data, avl->param) > 0) /*go to the right*/
	{
		curr = node->right_son;
		if (curr && avl->cmp_func(data, curr->data, avl->param) == 0)
		{
			if (getHeight(curr) == 1)
			{
				node->right_son = NULL;
				free(curr);
			}
			else if (HasOneChild(curr))
			{
				if (curr->left_son)
				{
					node->right_son = curr->left_son;
				}
				else
				{
					node->right_son = curr->right_son;
				}
				free(curr);
			}
			else /*node has 2 children*/
			{
				if (curr->right_son->left_son)
				{
					node->right_son = FindNextAndRemoveInRightSubTree(curr->right_son);
					node->right_son->right_son = curr->right_son;
				}
				else
				{
					node->right_son = curr->right_son;
				}
				node->right_son->left_son = curr->left_son;
				free(curr);
				node->right_son->height = 1 + max(getHeight(node->right_son->left_son), getHeight(node->right_son->right_son));
				return;
			}
		}
		else
		{
			AvlRemoveHelper(avl, node->right_son, data);
		}
	}
	node->height = 1 + max(getHeight(node->left_son), getHeight(node->right_son));
}

/**************for destroy**********/
static void AvlDestroyHelper(avl_node_t *node)
{
	if (node->left_son)
	{
		AvlDestroyHelper(node->left_son);
	}
	if (node->right_son)
	{
		AvlDestroyHelper(node->right_son);
	}
	free(node);
}
