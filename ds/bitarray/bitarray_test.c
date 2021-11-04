#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "bit_array.h"

#define ARRAYSIZE 64

void testSetAll();
void testResetAll();
void testSetOn();
void testSetOff();
void testSetBit();
void testGetValue();
void testFlip();
void testMirror();
void testCountOn();
void testCountOff();
void testRotR();
void testRotL();
void testToString();
void testToggleBit();
void testMirrorLut();

int main() {
	testSetAll();
	testResetAll();
	testSetOn();
	testSetOff();
	testSetBit();
	testGetValue();
	testFlip();
	testMirror();
	testCountOn();
	testCountOff();
	testRotR();
	testRotL();
	testToString();
	testToggleBit();
	testMirrorLut();
   	return 0;
}

void testSetAll()
{
	if(!(ULONG_MAX == BitArraySetAll())){
		printf("fail in %d", __LINE__);
	}
}

void testResetAll()
{
	if(!(0 == BitArrayResetAll())){
		printf("fail in %d", __LINE__);
	}
}


void testSetOn()
{
	bitarray_t b = BitArrayResetAll();
	char *c = "0001000000000000000000000000000000000000000000000000000000000000";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	
	s = BitArrayToString(b,s);
	b = BitArraySetOn(b, 60);
	s = BitArrayToString(b,s);

	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
		
	free(s);
	s = NULL;
	
}

void testSetOff()
{
	bitarray_t b = BitArraySetAll();

	char *c = "1111111111111111111111111111111111111111111111111111101111111111";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	
	b = BitArraySetOff(b, 10);
	s = BitArrayToString(b,s);


	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	
	
	free(s);
	s = NULL;
	
}

void testSetBit()
{
	bitarray_t b = BitArrayResetAll();	
	char *c = "0000000000000000000000000000000000000000000000000000000000000001";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	
	b = BitArraySetBit(b, 0, 1);
	s = BitArrayToString(b,s);

	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	free(s);
	s = NULL;
}

void testGetValue()
{
	bitarray_t b = BitArrayResetAll();
	b = BitArraySetOn(b, 45);
		
	if(!(1 == BitArrayGetValue(b, 45)))
	{
		printf("fail in %d\n", __LINE__);
	}
	
}

void testFlip()
{
	bitarray_t b = BitArraySetAll();
	char *c = "0010000000000000000000000000000000000000000000000000000000000000";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	
	b = BitArraySetOff(b, 61);
	b = BitArrayFlip(b);	
	s = BitArrayToString(b,s);
	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	free(s);
	s = NULL;
}

void testMirror()
{
	bitarray_t b = BitArrayResetAll();
	char *c = "1110000000000000000000000000000000000000000000000000000000000000";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	
	b = BitArraySetOn(b, 0);
	b = BitArraySetOn(b, 1);
	b = BitArraySetOn(b, 2);
	b = BitArrayMirror(b);
	s = BitArrayToString(b,s);
	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	free(s);
	s = NULL;

}

void testCountOn()
{
	bitarray_t b = BitArrayResetAll();
	b = BitArraySetOn(b, 0);
	b = BitArraySetOn(b, 5);
	b = BitArraySetOn(b, 45);
	if(!(3 == BitArrayCountOn(b)))
	{
		printf("fail in %d\n", __LINE__);
	}
	
}

void testCountOff()
{
	bitarray_t b = BitArrayResetAll();
	b = BitArraySetOn(b, 0);
	b = BitArraySetOn(b, 5);
	b = BitArraySetOn(b, 45);
	if(!(64 - 3 == BitArrayCountOff(b)))
	{
		printf("fail in %d\n", __LINE__);
	}
}

void testRotR()
{
	
	bitarray_t b = BitArrayResetAll();
	char *c = "0100100000000000000000000000000000000000000000000000000000000000";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	b = BitArraySetOn(b, 2);
	b = BitArraySetOn(b, 5);
	b = BitArrayRotR(b, 7);
	s = BitArrayToString(b,s);
	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	free(s);
	s = NULL;
		
}

void testRotL()
{
	
	bitarray_t b = BitArrayResetAll();
	char *c = "0000000000000000000000000000000000000000000000000000000100001000";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	b = BitArraySetOn(b, 60);
	b = BitArraySetOn(b, 1);
	b = BitArrayRotL(b, 7);
	s = BitArrayToString(b,s);
	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	free(s);
	s = NULL;
		
}

void testToString(){
	bitarray_t b = BitArrayResetAll();
	char *c = "0000000000000000000000000000000000000000000000000000000000000000";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	
	s = BitArrayToString(b,s);

	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	free(s);
	s = NULL;
}

void testToggleBit(){

	bitarray_t b = BitArrayResetAll();
	char *c = "0000100000000000000000000000000000000000000000000000000000000000";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	b = BitArrayToggleBit(b, 59);
	s = BitArrayToString(b,s);

	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	free(s);
	s = NULL;
}

void testMirrorLut()
{
	bitarray_t b = BitArrayResetAll();
	char *c = "1110000000000000000000000000000000000000000000000000000000000000";
	char *s = NULL;
	
	s = (char*)calloc(sizeof(char),ARRAYSIZE + 1);
	if(!s)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	
	b = BitArraySetOn(b, 0);
	b = BitArraySetOn(b, 1);
	b = BitArraySetOn(b, 2);
	b = BitArrayLutMirror(b);
	s = BitArrayToString(b,s);
	if(!(strncmp(c, s, 64) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}
	
	free(s);
	s = NULL;
}






