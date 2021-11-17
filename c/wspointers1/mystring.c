#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

#include "/home/dolev/git/dolev-arev/include/utils.h"
#include "mystring.h"

int main() 
{

	testStrCmp();
	testStrLen();
	testStrCpy();
	testStrnCpy();
	testStrCaseCmp();
	testStrChr();
	testStrDup();
	testStrCat();
	testStrnCat();
	testStrStr();
	testPalindrome();
	testSevenBoom(); 
	
	printf("tests are " ANSI_COLOR_GREEN "OK\n" ANSI_COLOR_RESET);
    	return 0;    	
}

/****************************TESTS******************************/

void testStrCmp()
{
	char* a = "ZZdfdfdf";
	char* b = "aZdfdfdf";
	char* c = "aZdfdfdf";
	char* d = "ekwjfw;fl";
	ASSERT(StrCmp(a, b) < 0);
	ASSERT(StrCmp(b,c) == 0);
	
	if(strcmp(a,d) < 0)
	{
		ASSERT(StrCmp(a, d) < 0);
	}else
	{
		if (strcmp(a,d) > 0)
		{
			ASSERT(StrCmp(a, d) > 0);
		} else {
			ASSERT(0 == StrCmp(a, d) );
		}
	}
}


void testStrLen()
{
	char* a = "dsjsdjs";
	char* b = "";
	ASSERT(StrLen(a) == strlen(a));
	ASSERT(StrLen(a) == 7);
	ASSERT(StrLen(b) == 0);
}

void testStrCpy()
{

	char *a = "Hello world!";
	char *c = NULL;
	char *d = NULL;
	char *e = NULL;
	char *b = NULL;
	
	b = (char*)malloc(strlen(a)+1);
	if(NULL == b){
		return;
	}
	
	d = (char*)malloc(strlen(a)+1);
	if(NULL == d){
		return;
	}

	c = StrCpy(b, a);
	e = strcpy(d, a);
	ASSERT(StrCmp(c,e) == 0);
	ASSERT(StrCmp(b,d) == 0);
	FREE(b);
	FREE(d);
}

void testStrnCpy()
{
	char *a = "Hello World!";
	char *d = NULL;
	char *b = NULL;
	char *c = NULL;
	char *e = NULL;
	
	b = (char*)calloc(10,1);
	if(NULL == b){
		return;
	}
	
	c = StrnCpy(b, a, 9);
	
	d = (char*)calloc(10,1);
	if(NULL == d){
		return;
	}
	
	e = strncpy(d, a, 9);
	
	ASSERT(StrCmp(c,e) == 0);
	
	ASSERT(StrCmp(c,"Hello Wor") == 0);
	
	ASSERT(StrCmp(b,d) == 0);
		
	FREE(b);
	FREE(d);
}

void testStrCaseCmp(){

	char *a = "ZZZZZwow wwww!!! ";
	char *b = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";
	if(strcasecmp(a,b) < 0){
		ASSERT(StrCaseCmp(a,b) < 0);
	}else {
		
		if (strcasecmp(a,b) == 0){
		ASSERT(StrCaseCmp(a,b) == 0);	
		}else{
		ASSERT(StrCaseCmp(a,b) > 0);
		}
	}
	ASSERT(StrCaseCmp(a,"zzzzzwow wwww!!! ") == 0);
}

void testStrChr(){
	char* a = "ZZZZZwow wwww!!! ";
	char* b = StrChr(a, 'w');
	char* c = strchr(a, 'w');
	char* z = "wow wwww!!! ";
	ASSERT(b == c);
	ASSERT(StrCmp(b,z) == 0);
}

void testStrDup(){
	char* a = "ZZZZZwow wwww!!! ";
	char* b = StrDup(a);
	char* c = NULL;
	c = (char*)strdup(a);
	ASSERT(StrCmp(b,c) == 0);
	FREE(b);
	FREE(c);
}

void testStrCat(){
	char a [1000]= "ZZZZZwow wwww!!! fdsdf";
	char *b = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";
	char c [1000]= "ZZZZZwow wwww!!! fdsdf";
	StrCat(a,b);
	strcat(c,b);
	ASSERT(StrCmp(StrCat(a,b), strcat(c,b))  == 0 );
}

void testStrnCat(){

	char a [1000]= "ZZZZZwow wwww!!! fdsdf";
	char *b = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";
	char c [1000]= "ZZZZZwow wwww!!! fdsdf";
	StrnCat(a,b, 1);
	strncat(c,b, 1);
	ASSERT(StrCmp(StrnCat(a,b, 7), strncat(c,b, 7)) == 0 );

}

void testStrStr(){
	
	char* a = "ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";	
	char* b ="!!";
	ASSERT(StrCmp(StrStr(a,b), strstr(a,b)) == 0);
}

void testStrSpn(){

	char* a = "!ZwwT ZZZZZwow wwwZZZZZwow wwww!!! w!!! ";	
	char* b ="w!!ZT";
	printf("%lu\n", StrSpn(a,b));
	printf("%lu\n", strspn(a,b));
	

}

void testPalindrome(){

	char* s = "ssss1s";
	char* a = "ss1ss1ss";
	ASSERT(Palindrome(s) == 0);

	ASSERT(Palindrome(a) == 1);

}

void testSevenBoom(){
	SevenBoom(1,41);
}


void testDeBug(){
	while(1){
	
	}
}

/*****************************END OF TESTS*******************************************/

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

size_t StrLen(const char *str)
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
  
   while(*str1){ 
      if(*str1 != *str2)
      {
         break;
      }
      str1++;
      str2++;
   }
   return *str1 - *str2;
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

int StrCaseCmp(const char *str1, const char *str2)
{
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

char *StrChr(const char* str, int c)
{
	char* current= (char *)str;
	
	assert(str != NULL);

	while(*current != '\0')
	{
		if(*current == c)
		{
			return current;
		}
		current++;
	}
	return NULL;

}

char *StrDup(const char *str){
	
	char* result = (char*)malloc(StrLen(str) + 1);
	assert(str != NULL);
	if(result == NULL){
		return NULL;
	}
	StrCpy(result, str);
	return result;
	
}

char *StrCat(char *destination, const char *source){
	
	int i = 0;
	int dest_len = StrLen(destination);
	assert(destination != NULL && source != NULL);
	for(; source[i] != '\0'; ++i){
		destination[dest_len + i] = source[i];
	}
	destination[dest_len + i] = '\0';
	
	return destination;
	
}

char* StrnCat (char* destination, const char* source, size_t num ){

	size_t i = 0;
	int dest_len = StrLen(destination);
	assert(destination != NULL && source != NULL);
	for(; '\0' != source[i] && i < num; ++i){
		destination[dest_len + i] = source[i];
	}
	destination[dest_len + i] = '\0';
	
	return destination;
	
}

char *StrStr(const char *haystack, const char *needle){
	size_t i = 0;
	size_t j = 0;
	assert(haystack != NULL && needle != NULL);
	for(; i < StrLen(haystack) - StrLen(needle); ++i){
	
		if(needle[0] == haystack[i]){
		
			for(; j < StrLen(needle); ++j){
				if(haystack[i+j] != needle[j]){
					break;
				}
			}
			return (char *)haystack + i;
			
		}
	
	}
	return NULL;
}

size_t StrSpn(const char *str1, const char *str2){

	char* start = (char*)str2;
	int count = 0;
	assert(str1 != NULL && str2 != NULL);
	
	while(*str1){
		str2 = start;
		while(*str2){
			
			if(*str1 == *str2){
				
				count++;
				break;	
			}
			str2++;
		}
			
		if(!*str2){
			return count;
		}
		str1++;
	}
	return count;
}

int Palindrome (char* str)
{
	size_t i = 0;
	assert(str);
	for(; i < StrLen(str)/2; i++){
		if(str[i] != str[StrLen(str) - i - 1]){
			return 0;
		}
	}
	
	return 1;
}


int isSeven(int current){
	int temp = current;
	if(current%7 == 0){
		return 1;
	}
	
	while(temp != 0){
		if(temp%10 == 7){
			return 1;
		}
		else{
			temp = temp/10;
		}
	}
	return 0;
	
}

void SevenBoom(int start, int finish){
	int i = start;
	
	if(start < finish){
		
		for(; i < finish; ++i){
			if(isSeven(i)){
				printf("BOOM\n");
			}
			else{
				printf("%d\n", i);
			}
		} 	
		
	}
	else{
		for(; i > finish; --i){
			if(isSeven(i)){
				printf("BOOM\n");
			}
			else{
				printf("%d\n", i);
			}
		}
	}
	
	
	
}



































