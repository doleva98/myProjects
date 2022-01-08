#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "dhcp.h"

typedef struct trie_node trie_node_t;

struct dhcp
{
	trie_node_t *root;
	ip_t net_mask;
	ip_t net_add, server_add, broadcast_add;
};

struct trie_node
{
	trie_node_t *to_zero;
	trie_node_t *to_one;
	int is_full;
};

static trie_node_t *TrieNodeCreate();
static ip_t StringToIP(char *ip);
static void DestroyHelper(trie_node_t *node);
static ip_t AllocateHelper(trie_node_t *node, ip_t level);
static int IsFull(trie_node_t *node);
static void FreeHelper(trie_node_t *node, ip_t ip, size_t n);
static void CountHelper(trie_node_t *node, size_t *count);
trie_node_t *FindNextInIp(trie_node_t *node, ip_t ip);

/*net_add is a string such "xxx.xxx.xxx.xxx"*/
/*net_mask is num of bits setOn*/
/* net mask is how much bits are for the server i can use 32 - net_mask - 3 */
dhcp_t *DHCPCreate(char *net_add, unsigned int net_mask)
{
	dhcp_t *dhcp = NULL;

	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if (!dhcp)
	{
		return NULL;
	}

	dhcp->root = TrieNodeCreate();
	if (!dhcp->root)
	{
		free(dhcp);
		return NULL;
	}

	/* assert net_add and net mask*/
	dhcp->net_add = StringToIP(net_add);
	dhcp->net_mask = net_mask;
	dhcp->broadcast_add = (dhcp->net_add | (0xFFFFFFFF >> net_mask));
	dhcp->server_add = dhcp->broadcast_add - 1;

	return dhcp;
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(dhcp);

	DestroyHelper(dhcp->root);
	free(dhcp);
}

size_t DHCPCountFree(const dhcp_t *dhcp)
{
	size_t sum = 0;

	assert(dhcp);
	CountHelper(dhcp->root, &sum);
	return (0xFFFFFFFF >> dhcp->net_mask) - sum - 3;
}

ip_t DHCPAllocIP(dhcp_t *dhcp)
{
	assert(dhcp);

	return dhcp->net_add | AllocateHelper(dhcp->root, 31 - dhcp->net_mask);
}

void DHCPFreeIP(dhcp_t *dhcp, ip_t ip_add)
{
	assert(dhcp);

	FreeHelper(dhcp->root, ip_add, 31 - dhcp->net_mask);
}

static trie_node_t *TrieNodeCreate()
{
	trie_node_t *trie_node = NULL;

	trie_node = (trie_node_t *)malloc(sizeof(trie_node_t));
	if (!trie_node)
	{
		return NULL;
	}

	trie_node->to_zero = NULL;
	trie_node->to_one = NULL;
	trie_node->is_full = 0;

	return trie_node;
}

static ip_t StringToIP(char *ip)
{
	char *token = NULL;
	size_t i = 3;
	const char s[2] = ".";
	ip_t num = 0;

	token = strtok(ip, s);

	while (token != NULL)
	{
		num |= atoi(token) << (i * 8);
		token = strtok(NULL, s);
		--i;
	}

	return num;
}

static void DestroyHelper(trie_node_t *node)
{
	if (!node)
	{
		return;
	}
	if (node->to_zero)
	{
		DestroyHelper(node->to_zero);
	}
	if (node->to_one)
	{
		DestroyHelper(node->to_one);
	}
	free(node);
	return;
}

static ip_t AllocateHelper(trie_node_t *node, ip_t level)
{

	ip_t temp = 0;

	if (level == 0)
	{
		if (!node->to_zero)
		{
			node->to_zero = TrieNodeCreate();
			node->to_zero->is_full = 1;
			return 0;
		}
		else
		{
			node->to_one = TrieNodeCreate();
			node->to_one->is_full = 1;
			node->is_full = 1;
			return 1;
		}
	}
	if (!node->to_zero)
	{
		node->to_zero = TrieNodeCreate();
	}
	if (!node->to_zero->is_full)
	{
		temp = AllocateHelper(node->to_zero, level - 1);
	}

	else
	{
		if (!node->to_one)
		{
			node->to_one = TrieNodeCreate();
		}
		if (!IsFull(node->to_one))
		{
			temp = AllocateHelper(node->to_one, level - 1) | (1 << level);
		}
	}

	if (node->to_zero && node->to_one)
	{
		if (IsFull(node->to_one) && IsFull(node->to_zero))
		{
			node->is_full = 1;
		}
	}
	return temp;
}

static int IsFull(trie_node_t *node)
{
	return node->is_full;
}

static void CountHelper(trie_node_t *node, size_t *count)
{
	if (!node->to_zero && !node->to_one)
	{
		++*count;
		return;
	}
	if (node->to_zero)
	{
		CountHelper(node->to_zero, count);
	}
	if (node->to_one)
	{
		CountHelper(node->to_one, count);
	}
}

static void FreeHelper(trie_node_t *node, ip_t ip, size_t n)
{
	if (!node)
	{
		return;
	}

	if (0 == n)
	{
		if (ip & 1)
		{
			free(node->to_one);
		}
		else
		{
			free(node->to_zero);
		}
		node->is_full = 0;
		return;
	}

	if (ip >> n & 1)
	{
		FreeHelper(node->to_one, ip, n - 1);
	}

	else
	{
		FreeHelper(node->to_zero, ip, n - 1);
	}

	if (!node->to_zero && !node->to_one)
	{
		free(node);
	}

	else if (node->is_full)
	{
		node->is_full = 0;
	}
}
