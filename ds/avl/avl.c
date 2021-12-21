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

static avl_node_t *BalanceTree(avl_t *avl, avl_node_t *node, const void *data);
static avl_node_t *RightRotate(avl_t *avl, avl_node_t *node);
static avl_node_t *LeftRotate(avl_t *avl, avl_node_t *node);
static avl_node_t *MinFromRightSubTree(avl_node_t *node);
static avl_node_t *Remove(avl_t *avl, avl_node_t *node, const void *data);

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
	int res = 0;
	if (AvlFind(avl, data))
	{
		return 1;
	}
	if (!avl->root)
	{
		avl->root = CreateNode(data);
		return !avl->root;
	}
	res = AvlInsertHelper(avl, avl->root, data);
	avl->root->height = 1 + max(getHeight(avl->root->left_son), getHeight(avl->root->right_son));
	if (avl->root->left_son)
	{
		avl->root->left_son = BalanceTree(avl, avl->root->left_son, data);
	}
	if (avl->root->right_son)
	{
		avl->root->right_son = BalanceTree(avl, avl->root->right_son, data);
	}
	avl->root = BalanceTree(avl, avl->root, data);
	return res;
}

void AvlRemove(avl_t *avl, const void *data)
{
	avl->root = Remove(avl, avl->root, data);
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
			result = !node->left_son;
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
			result = !node->right_son;
		}
	}
	node->height = 1 + max(getHeight(node->left_son), getHeight(node->right_son));
	if (node->left_son)
	{
		node->left_son = BalanceTree(avl, node->left_son, data);
	}
	if (node->right_son)
	{
		node->right_son = BalanceTree(avl, node->right_son, data);
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
	if (avl->cmp_func(data, node->data, avl->param) == 0)
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

/**************for destroy**********/
static void AvlDestroyHelper(avl_node_t *node)
{
	if (!node)
	{
		return;
	}
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

/**************Rotation***************/

static int GetBalance(avl_node_t *node)
{
	if (!node)
	{
		return 0;
	}
	return getHeight(node->left_son) - getHeight(node->right_son);
}

/*rotate a subtree that node is the root of him to the right*/
static avl_node_t *RightRotate(avl_t *avl, avl_node_t *node)
{
	avl_node_t *new_root = node->left_son;
	avl_node_t *T2 = new_root->right_son;

	new_root->right_son = node;
	node->left_son = T2;

	node->height = max(getHeight(node->left_son), getHeight(node->right_son)) + 1;
	new_root->height = max(getHeight(new_root->left_son), getHeight(new_root->right_son)) + 1;
	if (avl->root == new_root->right_son)
	{
		avl->root = new_root;
	}
	return new_root;
}

static avl_node_t *LeftRotate(avl_t *avl, avl_node_t *node)
{
	avl_node_t *new_root = node->right_son;
	avl_node_t *T2 = new_root->left_son;

	new_root->left_son = node;
	node->right_son = T2;

	node->height = max(getHeight(node->right_son), getHeight(node->left_son)) + 1;
	new_root->height = max(getHeight(new_root->right_son), getHeight(new_root->left_son)) + 1;
	if (avl->root == new_root->left_son)
	{
		avl->root = new_root;
	}
	return new_root;
}

static avl_node_t *BalanceTree(avl_t *avl, avl_node_t *node, const void *data)
{
	int balance = 0;
	int left_balance = 0;
	int right_balance = 0;

	node->height = 1 + max(getHeight(node->left_son), getHeight(node->right_son));

	if (node->left_son)
	{
		node->left_son = BalanceTree(avl, node->left_son, data);
	}
	if (node->right_son)
	{
		node->right_son = BalanceTree(avl, node->right_son, data);
	}

	(void)data;
	if (!node)
	{
		return NULL;
	}
	if (node->left_son)
	{
		left_balance = GetBalance(node->left_son);
	}
	if (node->right_son)
	{
		right_balance = GetBalance(node->right_son);
	}
	balance = GetBalance(node);

	if (left_balance > 1 || left_balance < -1)
	{
		BalanceTree(avl, node->left_son, data);
	}

	if (right_balance > 1 || right_balance < -1)
	{
		BalanceTree(avl, node->right_son, data);
	}

	/*left left*/
	if (balance > 1 && left_balance >= 0)
	{
		return RightRotate(avl, node);
	}
	/*right right*/
	else if (balance < -1 && right_balance <= 0)
	{
		return LeftRotate(avl, node);
	}
	/*left right*/
	else if (balance > 1 && right_balance <= 0)
	{
		node->left_son = LeftRotate(avl, node->left_son);
		return RightRotate(avl, node);
	}
	/*right left*/
	else if (balance < -1 && right_balance >= 0)
	{
		node->right_son = RightRotate(avl, node->right_son);
		return LeftRotate(avl, node);
	}

	node->height = 1 + max(getHeight(node->left_son), getHeight(node->right_son));

	return node;
}

static avl_node_t *Remove(avl_t *avl, avl_node_t *node, const void *data)
{
	if (!node)
	{
		return NULL;
	}
	if (avl->cmp_func(data, node->data, avl->param) == 0)
	{
		avl_node_t *temp = NULL;
		if (!node->right_son && !node->left_son)
		{
			free(node);
			return NULL;
		}
		else if (node->right_son)
		{
			temp = MinFromRightSubTree(node->right_son);
			temp->left_son = node->left_son;
			if (node->right_son != temp)
			{
				temp->right_son = node->right_son;
			}
		}
		else /*2 child*/
		{
			temp = node->left_son;
		}
		free(node);
		node = temp;
	}
	else if (avl->cmp_func(data, node->data, avl->param) > 0)
	{
		node->right_son = Remove(avl, node->right_son, data);
	}
	else
	{
		node->left_son = Remove(avl, node->left_son, data);
	}
	return BalanceTree(avl, node, data);
}

static avl_node_t *MinFromRightSubTree(avl_node_t *node)
{
	avl_node_t *temp = NULL;
	if (!node->left_son)
	{
		return node;
	}
	temp = MinFromRightSubTree(node->left_son);
	if (node->left_son == temp)
	{
		node->left_son = temp->right_son;
	}
	return temp;
}