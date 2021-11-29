#include "vsa.h"
#include <assert.h>
#include <stdio.h>

typedef struct FreeListNode fnode_t;
struct FreeListNode
{
	fnode_t *next;
	size_t status;
};

/* list of memory... */
struct VaribleAlloc
{
	fnode_t *head, *tail;
};

typedef enum {FREE = 0, OCCUP = 1} block_status;

static size_t AlignBlockSize(size_t block_size);
static void DeFragment(fnode_t *ptr);
static fnode_t *CorrNode(fnode_t *node);

/* get the free space in memory */
var_alloc_t* VSAInit(void *pool, size_t pool_size)
{ 
	var_alloc_t *vsa = NULL;
		
	assert(pool);
	
	while((size_t)pool % sizeof(size_t))
	{
		pool = (void*)((size_t)pool + 1);		
	}
	
	vsa = pool;
	vsa->head = (fnode_t*)((size_t)pool + sizeof(var_alloc_t));
	vsa->tail = (fnode_t*)((size_t)pool + pool_size - sizeof(fnode_t));
	
	vsa->head->status = FREE;
	vsa->tail->status = OCCUP;	
	
	vsa->tail->next = NULL;
	vsa->tail = (fnode_t*)((size_t)vsa->tail + sizeof(fnode_t));
	
	vsa->head->next = vsa->tail;
	vsa->head = (fnode_t*)((size_t)vsa->head + sizeof(fnode_t));
	
	return vsa;
}

/* return address for a block */
void* VSAAlloc(var_alloc_t* vsa, size_t block_size)
{
	fnode_t *temp = NULL;
	size_t size_req = AlignBlockSize(block_size) + sizeof(fnode_t);
	
	assert(vsa);
	
	temp = CorrNode(vsa->head);
	if(!temp->next)
	{
		return NULL;
	}
		
	while((size_t)temp < (size_t)CorrNode(vsa->tail))
	{
		if(FREE == temp->status)
		{
			DeFragment(temp);
			if((size_t)CorrNode(temp->next) - (size_t)temp > size_req)
			{
				fnode_t *new = NULL;
				new = (fnode_t*)((size_t)temp + size_req);;
				new->next = temp->next;
				new->status = FREE;
				temp->next = (fnode_t*)((size_t)new + sizeof(fnode_t));
				temp->status = OCCUP;
				return (void*)((size_t)temp + sizeof(fnode_t));
			}
		}
		
		temp = CorrNode(temp->next);
	}
	
	return NULL;
}

/* free the specific block */
void VSAFree(void* block)
{		
	fnode_t* temp = CorrNode(block);
	temp->status = FREE;
}


size_t LargestChunkAvailable(var_alloc_t* vsa)
{
	fnode_t *temp = NULL;
	size_t largest = 0;
	temp = CorrNode(vsa->head);
	while((size_t)temp < (size_t)CorrNode(vsa->tail))
	{		
		if(FREE == temp->status)
		{
			size_t diff;
			DeFragment(temp);
			
			diff = (size_t)CorrNode(temp->next) - (size_t)temp;
			if(diff > largest)
			{
				largest = diff;
			}			
		}
		temp = CorrNode(temp->next);			
	}
	return largest;
}

static size_t AlignBlockSize(size_t block_size)
{
	for(;(block_size % sizeof(size_t)); ++block_size);
	return block_size;
}

static void DeFragment(fnode_t *ptr)
{
	fnode_t *temp = ptr;

	assert(ptr);
	
	if(!temp->next)
	{
		return ;
	}
	while(FREE == CorrNode(temp->next)->status)
	{
		fnode_t *next_node = CorrNode(temp->next);
		
		temp->next = next_node->next;
		if(NULL == CorrNode(temp->next))
		{
			break;
		}		
	}
}

static fnode_t *CorrNode(fnode_t *node)
{
	return (fnode_t*)((size_t)node - sizeof(fnode_t));
}
