#include "/home/dolev/git/dolev-arev/include/utils.h"
#include "ws.h"

int main() 
{

   ex1(); 
   Logger("hello.txt");

   return 0;
}

void ex1()
{
	int i = 0;
	int j = 0;
	
	struct print_me
	{
		int value;
		void (*Print_p)(int);
	};
	
	struct print_me *array = NULL;
	CALLOC(array,10);
	
	for(; i < 10; ++i)
	{
		
		array[i].value = i*i;
		array[i].Print_p = Print;
	}
	
	for(; j < 10; ++j)
	{
		
		array[j].Print_p(array[j].value);
	}
	
	FREE(array);

}

void Print(int i)
{
	printf("%d\n",i);	
}

void Logger(char *nameFile)
{
	char *str = NULL;
	FILE *stream = NULL;
	printf("write here\n");
	CALLOC(str, 256);
	scanf("%s", str);
	while(*str != 's')
	{

		stream = fopen(nameFile, "a");
		if(!stream)
		{
			return;
		}
		
		fputs(str, stream);
		fputs("\n", stream);
		scanf("%s", str);
		fclose(stream);	
	
	}
	FREE(str);
}








