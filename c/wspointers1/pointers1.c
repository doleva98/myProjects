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
    	    	
    	testStrCat();
    	
    	return 0;    	
}

/*test for ex2*/

void testStrCpy()
{

	char *a = "Hello world!";
	char *c;
	char *b = (char*)malloc(strlen(a)+1);
	
	if(b == NULL){
		return;
	}

	printf("%lu\n", strlen(a)+1);
	c = StrCpy(b, a);
	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", c);
	free(b);
}

void testStrnCpy()
{
	char *a = "Hello World!";
	char *d;
	char *b;
	char *c;
	char *e;
	
	b = (char*)malloc(10);
	if(b == NULL){
		return;
	}
	
	c = StrnCpy(b, a, 9);
	
	
	d = (char*)malloc(10);
	if(d == NULL){
		return;
	}
	
	e = strncpy(d, a, 9);
	
	printf("%s\n", a);
	printf("%s\n", b);
	printf("%s\n", c);
	free(b);
	
	printf("%s\n", d);
	printf("%s\n", e);
	
	free(d);
}

void testStrCaseCmp(){

	char *a = "ZZZZZwow wwww!!! ";
	char *b = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";
	printf("%d\n", StrCaseCmp(a,b));
	printf("%d\n", strcasecmp(a,b));	
	
}

void testStrChr(){
	char* a = "ZZZZZwow wwww!!! ";
	char* b = StrChr(a, 'w');
	char* c = strchr(a, 'w');
	
	printf("%s\n", b);

	printf("%s\n", c);
}

void testStrDup(){
	char* a = "ZZZZZwow wwww!!! ";
	char* b = StrDup(a);
	printf("%s\n", b);
	free(b);
}

void testStrCat(){
	char a [1000]= "ZZZZZwow wwww!!! fdsdf";
	char *b = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";
	char c [1000]= "ZZZZZwow wwww!!! fdsdf";
	StrCat(a,b);
	strcat(c,b);
	printf("%s\n", a);
	printf("%s\n", c);
}

/*********************************************************************************************/
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
  
	
	assert(destination != NULL && source != NULL);
	
	for(;i < n ; ++i)
	{
		
		destination[i] = source[i];
		if(source[i] == '\0')
		{
			return result;
		}
		
	}
	destination[i] = '\0';
	return result;
	
}

int StrCaseCmp(const char *str1, const char *str2){
	assert(str1 != NULL && str2 != NULL);
  
   	while(*str1){  /*why dont you check (*str1 && *str2)?*/
      		if(tolower(*str1) != tolower(*str2))
      	{
         	break;
      	}
      		str1++;
      		str2++;
   	}
   	return tolower(*str1) - tolower(*str2);

}

char *StrChr(const char* str, int c){
	char* current= (char *)str;
	
	assert(str != NULL);

	while(*current != '\0'){
		if(*current == c){
			return current;
		}
		current++;
	}
	return NULL;

}

char *StrDup(const char *str){

	char* result = (char*)malloc(StrLen(str) + 1);
	if(result == NULL){
		return NULL;
	}
	StrCpy(result, str);
	return result;
	
}

char *StrCat(char *destination, const char *source){
	
	int i = 0;
	int dest_len = StrLen(destination);
	
	for(; source[i] != '\0'; ++i){
		destination[dest_len + i] = source[i];
	}
	destination[dest_len + i] = '\0';
	
	return destination;
	
}











































