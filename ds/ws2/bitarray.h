#include "/home/dolev/git/dolev-arev/include/utils.h"

#ifndef __BITARRAY_H__
#define __BITARRAT_H__

#if sizeof(size_t) == 8
	typedef unsigned long bitarray_t;
#else
	typedef unsigned long long bitarray_t;
#endif

	bitarray_t *BitArraySetAll(bitarray_t *ba);
	bitarray_t *BitArraySetOn(bitarray_t *ba);
	size_t BitArrayGetVal(bitarray_t *ba, size_t index);

	bitarray_t *BitArrayRotR(bitarray_t *ba, size_t n);
	bitarray_t *BitArrayRotL(bitarray_t *ba, size_t n);
	
	size_t BitArrayCountOn(bitarray_t *ba);
	size_t BitArrayCountOff(bitarray_t *ba);

#endif

