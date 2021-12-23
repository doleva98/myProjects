#include <stdio.h>
#include <stdlib.h>
#include "ht.h"
#include "doubly_linked_list.h"
struct Hash
{
	hash_func_t hash_func;
	cmp_func_t cmp_func;
	size_t size;
	dlist_t **array;
};

static int PlusOne(void *data, void *param);

/* Create new hash table*/
hash_t *HashCreate(hash_func_t hash_func, cmp_func_t cmp_func, size_t hash_size)
{
	hash_t *hash = NULL;

	hash = (hash_t *)malloc(sizeof(hash_t));
	if (!hash)
	{
		return NULL;
	}
	hash->hash_func = hash_func;
	hash->cmp_func = cmp_func;
	hash->size = hash_size;
	hash->array = (dlist_t **)calloc(sizeof(dlist_t **), hash_size);
	if (!hash->array)
	{
		free(hash);
		return NULL;
	}
	return hash;
}

/* Destroy hash table*/
void HashDestroy(hash_t *hash)
{
	size_t i;
	for (i = 0; i < hash->size; ++i)
	{
		if (hash->array[i])
		{
			DListDestroy(hash->array[i]);
		}
	}
	free(hash->array);
	free(hash);
}

/* Insert a new data - 0 if succes, 1 fail */
int HashInsert(hash_t *hash, const void *data)
{
	int index = 0;

	index = hash->hash_func(data) % hash->size;
	if (!hash->array[index])
	{
		hash->array[index] = DListCreate();
	}
	DListInsert(DListBegin(hash->array[index]), data);
	return 0;
}

/* Remove a data from hash table */
void HashRemove(hash_t *hash, const void *data)
{
	int index = 0;

	index = hash->hash_func(data) % hash->size;
	if (hash->array[index])
	{
		DListRemove(DListFind(DListBegin(hash->array[index]), DListEnd(hash->array[index]), hash->cmp_func, (void *)data));
	}
}

/* Number of element in table in total */
size_t HashSize(hash_t *hash)
{
	size_t count = 0;
	HashForEach(hash, PlusOne, &count);
	return count;
}

/* If hash table is Empty return 1 */
int HashIsEmpty(hash_t *hash)
{
	return 0 == HashSize(hash);
}

/* Find a data in the table  */
const void *HashFind(hash_t *hash, const void *data)
{
	int index = 0;
	const void *iter_res_data = NULL;

	index = hash->hash_func(data) % hash->size;
	if (!hash->array[index])
	{
		return NULL;
	}

	iter_res_data = DListIterGetData(DListFind(DListBegin(hash->array[index]),
											   DListEnd(hash->array[index]), hash->cmp_func, (void *)data));

	if (iter_res_data)
	{
		HashRemove(hash, data);
		HashInsert(hash, data);
	}
	return iter_res_data;
}

/* Execute operation on each element in table */
int HashForEach(hash_t *hash, hash_action_func_t action_func, void *param)
{
	size_t i;
	int res = 0;
	for (i = 0; i < hash->size; ++i)
	{
		if (hash->array[i])
		{
			res = !DListForEach(DListBegin(hash->array[i]), DListEnd(hash->array[i]), action_func, param);
		}
	}

	return !res;
}

static int PlusOne(void *data, void *param)
{
	(void)data;
	++*(size_t *)param;
	return 1;
}

float HashLoad(hash_t *hash)
{
	return HashSize(hash) / hash->size;
}