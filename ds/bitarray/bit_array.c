#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "bit_array.h"

#define ARRAYSIZE 64

bitarray_t BitArraySetAll()
{
	return ULONG_MAX;
}

bitarray_t BitArrayResetAll()
{
	return 0UL;
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
	bitarray_t temp = BitArrayResetAll();
		
	for(i = 0; i < steps % ARRAYSIZE; ++i)
	{
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
	bitarray_t temp = BitArrayResetAll();
		
	for(i = 0; i < steps % ARRAYSIZE; ++i)
	{
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

bitarray_t BitArrayLutMirror(bitarray_t array)
{	

	bitarray_t a [12];
	a[0] = 0xFFFFFFFF00000000;
	a[1] = 0x00000000FFFFFFFF;
	a[2] = 0xFFFF0000FFFF0000;
	a[3] = 0x0000FFFF0000FFFF;
	a[4] = 0xFF00FF00FF00FF00;
	a[5] = 0x00FF00FF00FF00FF;
	a[6] = 0xF0F0F0F0F0F0F0F0;
	a[7] = 0x0F0F0F0F0F0F0F0F;
	a[8] = 0xCCCCCCCCCCCCCCCC;
	a[9] = 0x3333333333333333;
	a[10] = 0xAAAAAAAAAAAAAAAA;
	a[11] = 0x5555555555555555;
	
	array = (array & a[0]) >> 32 | (array & a[1]) << 32;
	array = (array & a[2]) >> 16 | (array & a[3]) << 16;
	array = (array & a[4]) >> 8 | (array & a[5]) << 8;
	array = (array & a[6]) >> 4 | (array & a[7]) << 4;
	array = (array & a[8]) >> 2 | (array & a[9]) << 2;
	array = (array & a[10]) >> 1 | (array & a[11]) << 1;
	
	return array;
}

/* extern size_t BitArrayCountOnLUT(bitarray_t array)
{

	unsigned char lookuptable[256] = { B6(0), B6(1), B6(1), B6(2) };
	size_t count = 0;
	assert(array);
	count = lookuptable[array & 0xff] +
	lookuptable[(array >> 8) & 0xff] +
	lookuptable[(array >> 16) & 0xff] +
	lookuptable[(array >> 24) & 0xff] +
	lookuptable[(array >> 32) & 0xff] +
	lookuptable[(array >> 40) & 0xff] +
	lookuptable[(array >> 48) & 0xff] +
	lookuptable[(array >> 56) & 0xff];
	return count;

}
 */













