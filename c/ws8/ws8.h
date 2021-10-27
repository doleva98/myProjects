#include "/home/dolev/git/dolev-arev/include/utils.h"

typedef enum 
{
	et_int,
	et_float,
	et_string
}ElementType;


typedef struct
{
	ElementType type;
	
	int i;
	float f;
	char str [100];
	
}Element;


void f_print (Element *element, int len);
void f_add (Element *element, int len, int valueToAdd);
void f_cleanup(Element *element, int len);
void ws8();
void testMacros();
