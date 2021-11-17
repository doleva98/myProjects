/*hello guys this is a test for circular queue
if it doesnt print anything it is ok (slava style)
credit for Daniel and Dolev*/

#include <stdio.h>
#include "circular_buffer.h"



int main()
{
	int a [3] = {4000, 16, 650};
	int test = 0;
	cbuffer_t *cbuffer = CBufferCreate(10);
	
	if(!(CBufferIsEmpty(cbuffer) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferCapacity(cbuffer) == 10))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferFreeSpace(cbuffer) == 10))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferWrite(cbuffer, &a[0], 4) == 0))/*4000*/
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferWrite(cbuffer, &a[1], 4) == 0))/*4000, 16*/
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferRead(cbuffer, &test, 4) == 0))/*16*/
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(test == 4000))
	{
		printf("fail in %d\n", __LINE__);
	}
	if(!(CBufferFreeSpace(cbuffer) == 6))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferWrite(cbuffer, &a[2], 4) == 0))/*16, -650*/
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferFreeSpace(cbuffer) == 2))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferRead(cbuffer, &test, 4) == 0))/*-650*/
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(test == 16))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferFreeSpace(cbuffer) == 6))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferWrite(cbuffer, &a[0], 4) == 0))/*-650, 4000*/
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferRead(cbuffer, &test, 4) == 0))/*4000*/
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(test == 650))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferIsEmpty(cbuffer) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	if(!(CBufferCapacity(cbuffer) == 10))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	CBufferDestroy(cbuffer);
	
	return 0;
}
