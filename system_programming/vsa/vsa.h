#ifndef __VARIABLE_SIZE_ALLOCATOR_H__
#define __VARIABLE_SIZE_ALLOCATOR_H__

#include <stddef.h>

/* list of memory... */
typedef struct VaribleAlloc var_alloc_t;

/* get the free space in memory */
extern var_alloc_t* VSAInit(void *pool, size_t pool_size);

/* return address for a block */
extern void* VSAAlloc(var_alloc_t* vsa, size_t block_size);

/* free the specific block */
extern void VSAFree(void* block);

/* return the largest free block size */
extern size_t LargestChunkAvailable(var_alloc_t* vsa);

#endif