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
	

























