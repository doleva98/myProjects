#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "fsa.h"

typedef struct fsanode
{
	struct fsanode *next;
}FSAnode;

/* list of memory... */
struct FixedAlloc
{
	size_t free_slots;
	size_t block_capacity;
	FSAnode *head;
};

size_t FSAllocSuggestSize(size_t num_blocks, size_t block_size)
{	
	while(block_size % sizeof(size_t))
	{
		++block_size;
	} 
	return sizeof(fixed_alloc_t) + block_size*num_blocks;	
}

/* get the free space in memory */
fixed_alloc_t* FSAllocInit(void *pool, size_t pool_size ,size_t block_size )
{	
	fixed_alloc_t *alloc = NULL;
	FSAnode *curr = NULL;
	
	assert(pool && pool_size > sizeof(fixed_alloc_t));
	
	alloc = pool;
	alloc->free_slots = 0;
	alloc->head = (FSAnode*)((size_t)pool + sizeof(fixed_alloc_t));
	alloc->block_capacity = (pool_size - sizeof(fixed_alloc_t))/block_size;
	curr = alloc->head;
	
	while((size_t)curr + block_size-1< (size_t)pool + pool_size)
	{
		curr->next = (FSAnode*)((size_t)curr + block_size);
		curr = curr->next;
		++alloc->free_slots;
	}
	
	return alloc;
}

/* return address for a block */
void *FSAllocAlloc(fixed_alloc_t* alloc)
{
	void *tmp = NULL;
	
	assert(alloc->free_slots > 0);
	
	tmp = alloc->head;
	alloc->head = alloc->head->next;
	--alloc->free_slots;
	return tmp;
}

/* free the specific block */

void FSAllocFree(fixed_alloc_t* alloc, void* block)
{
	assert(alloc->block_capacity > alloc->free_slots && alloc && block);

	((FSAnode*)block)->next = alloc->head;
	alloc->head = block;
	++alloc->free_slots;
}


size_t FSAllocCountFree(fixed_alloc_t* alloc)
{
	assert(alloc);
	return alloc->free_slots;
}
