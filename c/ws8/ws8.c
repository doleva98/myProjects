#include "ws8.h"

struct point
{
	int x;
	int y;
};

int main() {
    struct point p = {100,3};
    int *n = (int *)&p;
    ws8();
    testMacros();
    

    printf("%d\n", n[1]);
    
   return 0;
}

#define ARRAY_SIZE 3

void ws8()
{

	Element elemArr [ARRAY_SIZE];
	

	elemArr[0].type = et_int;
	elemArr[0].i = 4;
	
	elemArr[1].type = et_float;
	elemArr[1].f = 16.99;

	elemArr[2].type = et_string;
	strcpy(elemArr[2].str, "hello world");
	
	f_print(elemArr, ARRAY_SIZE);
	
	f_add(elemArr, ARRAY_SIZE, 10);
	printf("------------------------\n");
	f_print(elemArr, ARRAY_SIZE);
	
}

void f_print (Element *element, int len)
{
	int i = 0;
	for(; i < len; ++i)
	{
		switch(element[i].type)
		{
			case et_int:
				printf("%d\n", element[i].i);
				break;
			case et_float:
				printf("%f\n", element[i].f);
				break;
			case et_string:
				printf("%s\n", element[i].str);
				break;
		}
	}
}

void f_add (Element *element, int len, int valueToAdd)
{
	int i = 0;
	char val [100];
	for(; i < len; ++i)
	{
		switch(element[i].type)
		{
			case et_int:
				element[i].i += valueToAdd;
				break;
			case et_float:
				element[i].f += (float)valueToAdd;
				break;
			case et_string:
				sprintf(val, "%d", valueToAdd);
				strcat(element[i].str, val);
				break;
		}
	}
}

/*
void f_cleanup(Element *element, int len)
{
	int i = 0;
	ElementType need cleanup;
	for(; i < len; ++i)
	{
		switch(element[i].type)
		{
			case et_int:
				printf("%d\n", element[i].i);
				break;
			
		}
	}
}
*/

#define MAX2(a, b) ((a) > (b)) ? (a): (b)

#define MAX3(a, b, c)\
 	MAX2(MAX2((a),(b)),(c))

#define SIZEOF_VAR( var ) ((size_t)(&(var)+1)-(size_t)(&(var))) 
#define SIZEOF_TYPE(object) (size_t)(1 + ((object*)0))

void testMacros()
{
	int *a = NULL;
	int b = 3;
	char d = '3';
	
	ASSERT(1040 == MAX2(30,1040));
	ASSERT(100002 == MAX3(100002,30,1040));
	ASSERT(8 == MAX3(100002,30,1040));
	ASSERT(8 == SIZEOF_VAR(a));
	ASSERT(4 == SIZEOF_VAR(b));
	ASSERT(1 == SIZEOF_VAR(d));
	printf("\nnow %lu\n", SIZEOF_TYPE(int));
}


























