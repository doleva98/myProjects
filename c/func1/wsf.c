#include <stdio.h>
#include <stdlib.h>
#include "/home/dolev/git/dolev-arev/include/utils.h"
#include "wsf.h"



int main() {
 	LUTInput();
	TypeIf();
	
   	return 0;
}

void LUTInput()
{
	typedef void (*foo_t)(void);
	char input = '0';
	int i = 0;
	foo_t array [127];
	for(; i < 127; ++i)
	{
		array[i] = DoNothing;
	}
	array['A'] = PrintA;
	array['T'] = PrintT;
	
	printf("press A or T or Esc\n");
	while(27 != input){

		scanf("%c", &input);
		array[input]();
	}
		
}

void DoNothing()
{

}

void PrintA()
{
	printf("A-pressed\n");
}

void PrintT()
{
	printf("T-pressed\n");
}

void SwitchInput()
{
	char input = '0';
	printf("press A or T or Esc\n");
	while(27 != input ){
		scanf("%c", &input);
		switch(input)
		{
			case 'A':
				printf("A-pressed\n");
				break;
			case 'T':
				printf("T-pressed\n");
				break;
		}
	}
}

void IfElseInput()
{
	char input = '0';
	printf("press A or T or Esc\n");
	while(27 != input)
	{
		scanf("%c", &input);
		if('A' == input)
		{
			printf("A-pressed\n");
		}
		else if('T' == input)
		{
			printf("T-pressed\n");
		}
		
		
	}
}

void TypeIf()
{
	int (*SumThis)(int,int) = add;
	
	typedef double elol;
	typedef int wow;
	typedef unsigned char koof;
	
	typedef int array[3];
	
	typedef int (*AddThis)(int,int);
	
	AddThis hello = add;
	
	array r = {1,2,3};
	
	elol i = 10;
	
	ASSERT(8 == sizeof(i));
	ASSERT(15 == SumThis(10,5));
	ASSERT(6 == hello(5,1));
	ASSERT(12 == sizeof(r));

	
}

int add(int i, int k){
	return i+k; 
}
