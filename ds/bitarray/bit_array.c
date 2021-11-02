#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bit_array.h"

#define ARRAYSIZE 64

bitarray_t BitArraySetAll()
{
	return ULONG_MAX;
}

bitarray_t BitArrayResetAll()
{
	return 0;
}

bitarray_t BitArraySetOn(bitarray_t array, size_t idx)
{
	return array|(1UL<<idx);
}

bitarray_t BitArraySetOff(bitarray_t array, size_t idx){
	return array&(~(1UL<<idx));
}

bitarray_t BitArraySetBit(bitarray_t array, size_t idx, bitstate_t value)
{
	if(value)
	{
		return BitArraySetOn(array, idx);
	}
	else
	{
		return BitArraySetOff(array, idx);
	}		
}

size_t BitArrayGetValue(bitarray_t array, size_t idx)
{	
	return (array>>idx) == 1;

}

bitarray_t BitArrayFlip(bitarray_t array)
{
	return ~array;	
}


bitarray_t BitArrayMirror(bitarray_t array)
{
	array = (array & 0xFFFFFFFF00000000) >> 32 | (array & 0x00000000FFFFFFFF) << 32;
	array = (array & 0xFFFF0000FFFF0000) >> 16 | (array & 0x0000FFFF0000FFFF) << 16;
	array = (array & 0xFF00FF00FF00FF00) >> 8 | (array & 0x00FF00FF00FF00FF) << 8;
	array = (array & 0xF0F0F0F0F0F0F0F0) >> 4 | (array & 0x0F0F0F0F0F0F0F0F) << 4;
	array = (array & 0xCCCCCCCCCCCCCCCC) >> 2 | (array & 0x3333333333333333) << 2;
	array = (array & 0xAAAAAAAAAAAAAAAA) >> 1 | (array & 0x5555555555555555) << 1;
	return array;
}

size_t BitArrayCountOn(bitarray_t array)
{
	size_t i = 0;
	size_t count = 0;
	for(; i < ARRAYSIZE; ++i)
	{	
		count += 1 & (array >> i);	
	}
	return count;
}

size_t BitArrayCountOff(bitarray_t array)
{
	return ARRAYSIZE - BitArrayCountOn(array);
}

bitarray_t BitArrayRotR(bitarray_t array, size_t steps)
{
	size_t i = 0;
	bitarray_t temp;
	
	if(steps % ARRAYSIZE == 0)
	{
		return array;
	}
		
	for(i = 0; i < steps % ARRAYSIZE; ++i)
	{
		temp = BitArrayResetAll();
		temp = array & 0x0000000000000001;
		temp <<= 63;
		array >>= 1;
		array |= temp;		
	}
	return array;

}

bitarray_t BitArrayRotL(bitarray_t array, size_t steps)
{

	size_t i = 0;
	bitarray_t temp;
	
	if(steps % ARRAYSIZE == 0)
	{
		return array;
	}
		
	for(i = 0; i < steps % ARRAYSIZE; ++i)
	{
		temp = BitArrayResetAll();
		temp = array & 0x8000000000000000;
		temp >>= 63;
		array <<= 1;
		array |= temp;		
	}
	return array;

}

char *BitArrayToString(bitarray_t array, char *dest)
{
	int i = 0;
	
	for(; i < ARRAYSIZE; ++i)
	{	
		dest[i] = '0' + (1 & (array >> (bitarray_t)(ARRAYSIZE - 1 - i)));
	}

	dest[ARRAYSIZE] = '\0';
	
	return dest;
}

bitarray_t BitArrayToggleBit(bitarray_t array, size_t idx)
{
	if(array&(1<<idx))
	{
		array = BitArraySetOff(array, idx);
	}
	else
	{
		array = BitArraySetOn(array, idx);
	}
	return array;
}















