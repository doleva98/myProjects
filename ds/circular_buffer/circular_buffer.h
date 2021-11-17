#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <unistd.h>

typedef struct CBuffer cbuffer_t;

/*creates new circular buffer*/
extern cbuffer_t *CBufferCreate(size_t size);

/*destroys circular buffer*/
extern void CBufferDestroy(cbuffer_t *cbuffer);

/* write to a circular buffer */
extern ssize_t CBufferWrite(cbuffer_t *cbuffer, const void *buf, size_t cnt);

/* read from a circular buffer*/
extern ssize_t CBufferRead(cbuffer_t *cbuffer, void *buf, size_t cnt);

/*returns the number of free bytes to write */
extern size_t CBufferFreeSpace(const cbuffer_t *cbuffer);

/*checks if the circular buffer is empty*/
extern int CBufferIsEmpty(const cbuffer_t *cbuffer);	/* return value empty - 1, not empty - 0 */

/*returns buffer size*/
extern size_t CBufferCapacity(const cbuffer_t *cbuffer);

#endif
