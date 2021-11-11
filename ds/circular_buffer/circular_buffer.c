#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "circular_buffer.h"

struct CBuffer
{	
	size_t capacity;
	size_t size;
	size_t front;
	size_t rear;
	char arr [1];
};

/*creates new circular buffer*/
cbuffer_t *CBufferCreate(size_t size)
{
	
	cbuffer_t *cbuffer = (cbuffer_t*)calloc(size + sizeof(cbuffer_t),1);
	if(!cbuffer)
	{
		return NULL;
	}
	cbuffer->size = 0;
	cbuffer->capacity = size;
	cbuffer->front = size;
	cbuffer->rear = size;
	return cbuffer;
}

/*destroys circular buffer*/
void CBufferDestroy(cbuffer_t *cbuffer)
{
	assert(cbuffer);
	free(cbuffer);
}

/* write to a circular buffer without overwrite return 0 to cnt value*/
ssize_t CBufferWrite(cbuffer_t *cbuffer, const void *buf, size_t cnt)
{	
	size_t howMuch;
	assert(cbuffer);
	assert(buf);
	
	if(CBufferFreeSpace(cbuffer) == 0)
	{
		return 0;
	}
	
	if(cnt > CBufferFreeSpace(cbuffer))
	{
		return -1;
	}
	
	howMuch = cbuffer->capacity - cbuffer->rear;
	cbuffer->size += cnt;
	if(cnt < howMuch)
	{
		memcpy(cbuffer + cbuffer->rear, buf, cnt);
		cbuffer->rear += cnt;
		return cnt;
	}
	else
	{
		memcpy(cbuffer + cbuffer->rear, buf, howMuch);
		memcpy(cbuffer + 3, buf, cnt - howMuch);
		cbuffer->rear = cnt - howMuch;
		return cnt;
	}
	
	return -1;
}

/* read from a circular buffer*/
ssize_t CBufferRead(cbuffer_t *cbuffer, void *buf, size_t cnt)
{
	size_t howMuch;
	assert(cbuffer);
	assert(buf);
	
	if(cnt > cbuffer->size)
	{
		return -1;
	}
	
	howMuch = cbuffer->capacity - cbuffer->front;
	cbuffer->size -= cnt;
	if(cnt < howMuch)
	{
		memcpy(buf, cbuffer + cbuffer->front, cnt);
		cbuffer->front += cnt;
		return cnt;
	}
	else
	{
		memcpy(buf,cbuffer + cbuffer->front, howMuch);
		memcpy(buf, cbuffer + 3, cnt - howMuch);
		cbuffer->front = cnt - howMuch;
		return cnt;
	}
	return -1;
}

/*returns the number of free bytes to write */
size_t CBufferFreeSpace(const cbuffer_t *cbuffer)
{
	assert(cbuffer);
	return cbuffer->capacity - cbuffer->size;
}

/*checks if the circular buffer is empty*/
int CBufferIsEmpty(const cbuffer_t *cbuffer){
	assert(cbuffer);
	return cbuffer->size == 0;
	
}
	/* return value empty - 1, not empty - 0 */

/*returns buffer size*/
size_t CBufferCapacity(const cbuffer_t *cbuffer)
{
	assert(cbuffer);
	return cbuffer->capacity;
	
}







