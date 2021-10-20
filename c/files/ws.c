#include "/home/dolev/git/dolev-arev/include/utils.h"
#include "ws.h"

int main() 
{

   ex1(); 
   Logger("h.txt");

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

	char *input = NULL;
	FILE *fp = NULL;
	int i;
	const int NUM_OF_FUNCS = 5;
	
	typedef struct 
	{	
		char *str;
		int (*CmpFunc)(char*, char*);
		void (*OperationFunc)(FILE*)(char*)(char*);	
	}funcLogger_t;	
	
	funcLogger_t FuncArray [NUM_OF_FUNCS]
	
	CALLOC(input, 256);
	
	FuncArray[0].str = "-remove";
	FuncArray[0].CmpFunc = StrCmp;
	FuncArray[0].OperationFunc = RemoveFile;	
	
	FuncArray[1].str = "-count";
	FuncArray[1].CmpFunc = StrCmp;
	FuncArray[1].OperationFunc = CountLines;	

	FuncArray[2].str = "-exit";
	FuncArray[2].CmpFunc = StrCmp;
	FuncArray[2].OperationFunc = ExitProgram;	
	
	FuncArray[3].str = "<";
	FuncArray[3].CmpFunc = isToFirst;
	FuncArray[3].OperationFunc = AddFirstToFile;
	
	FuncArray[4].str = "";
	FuncArray[4].CmpFunc = AlwaysTrue;
	FuncArray[4].OperationFunc = WriteToFile;	
	
	printf("write here\n");
	fgets(input, 256, stdin);
	
	while(*input != 's')
	{
	

		OPENFILE(fp, nameFile, "a");
		
		for(i = 0; i < NUM_OF_FUNCS, ++i)
		{
			if( 0 == FuncArray[i].CmpFunc(FuncArray[i].str, input)
			{
				FuncArray[i].OperationFunc(fp, nameFile, input);
				break;
			}	
		}
		fgets(input, 256, stdin);
	}
	

	FREE(input);
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

int isToFirst(const char* str1, const char* str2)
{
	return !(*str1 == '<');
}

int AlwaysTrue(const char* str1, const char* str2)
{
	return 0;
}

STATUS_FUNC RemoveFile(FILE* fp, char *FileName, char *input)
{	
	fclose(fp);	
	remove(FileName);
	return SUCCESS_t;
}

STATUS_FUNC CountLines(FILE* fp, char *FileName, char *input)
{
    printf("%d", HowManyLines(fp));
    fclose(fp);	
    return SUCCESS_t;
}

STATUS_FUNC ExitProgram(FILE* fp, char *FileName, char *input)
{
	fclose(fp);
	FREE(input);	
	exit(1);
    return SUCCESS_t;
}

STATUS_FUNC AddFirstToFile(FILE* fp, char *FileName, char *input)
{
	
	fseek(fp, 0, SEEK_SET);
	fprintf(fp,"%s", ++input);
	fseek(fp, 0, SEEK_END);
	
	
	fclose(fp);
	return SUCCESS_t;	
}

STATUS_FUNC WriteToFile(FILE* fp, char *FileName, char *input)
{
	fprintf(fp,"%s", input);
	fclose(fp);
	return SUCCESS_t;	
}

int HowManyLines(FILE* fp)
{
	char ch = '\0';
	int lines = 0;
	while(!feof(fp))
	{
	  ch = fgetc(fp);
	  if(ch == '\n')
	  {
	    lines++;
	  }
	}
	return lines;
}






