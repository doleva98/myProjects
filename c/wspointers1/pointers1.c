#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "mystring.h"

/*ex 1*/
void swap(int* a, int* b);
void copyArray(int a [], int b [], int len);
int StrLen(const char *str);
int StrCmp(const char* str1, const char* str2);
void swapTwoSizeT(size_t* a, size_t* b);
void swapTwoSizeTPointers(size_t** a, size_t** b);
void useSwap(size_t** a, size_t** b);



int main() 
{

    	
    	testStrnCpy();
    	
    	return 0;    	
}

/*test for ex2*/

void testStrCpy()
{

	char *a = "hello world";
	char b [StrLen(a)];
	char *c;
	c = StrCpy(b, a);
	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", c);
}

void testStrnCpy()
{
	
	char *a = "hello world";
	char b [StrLen(a)];
	char *c;
	c = StrnCpy(b, a, 8);
	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", c);
	
}


/*ex1*/
void swap(int* a, int* b)
{

int temp = *a;
*a = *b;
*b = temp;

}

void copyArray(int a [], int b [], int len)
{
  int i = 0;

   for(;i < len; i++)
   {
      b[i] = a[i];
   }
}

int StrLen(const char *str)
{ 
   int result = 0;  
   assert(str);   
   while(str[result]){
   	result++;
   	
   }
   return result;
}

int StrCmp(const char* str1, const char* str2)
{ 
   assert(str1);
   assert(str2);
  
   while(*str1){  /*why dont you check (*str1 && *str2)?*/
      if(*str1 != *str2)
      {
         break;
      }
      str1++;
      str2++;
   }
   return *(const unsigned char*) str1 - *(const unsigned char*) str2; /*why do you have to change to unsinged char? you lose information if str1 is less than str2 (in original function it returns a negative value)*/
}


void swapTwoSizeT(size_t* a, size_t* b)
{

   size_t temp = *a;
   *a = *b;
   *b = temp;
}

void swapTwoSizeTPointers(size_t** a, size_t** b)
{
   size_t* temp = *a;
   *a = *b;
   *b = temp;
}

void useSwap(size_t** a, size_t** b)
{
	swapTwoSizeT(*a, *b);
}

/*ex2*/

char* StrCpy(char* destination, const char* source)
{
	int i = 0;
	char *result = destination;
	assert(destination != NULL && source != NULL);
	
	while(1)
	{
		*destination = *source;
		
		if( *source == '\0'){
			break;
		}
		
		source++;
		destination++;
	}
	
	return result;
}

char *StrnCpy(char *destination, const char *source, size_t n)
{
	size_t i = 0;
	char *result = destination;
	assert(destination != NULL && source != NULL);
	
	while( i < n )
	{
	
		
	
	}
		
	return result;
	
}













































