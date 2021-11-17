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
	STATUS_FUNC ReturnValue = 0;	
	funcLogger_t *FuncArray = NULL;
	
	CALLOC(FuncArray, 5);
	
	CALLOC(input, 256);
	
	FuncArray[0].str = "-remove\n";
	FuncArray[0].CmpFunc = StrCmp;
	FuncArray[0].OperationFunc = RemoveFile;	
	
	FuncArray[1].str = "-count\n";
	FuncArray[1].CmpFunc = StrCmp;
	FuncArray[1].OperationFunc = CountLines;	

	FuncArray[2].str = "-exit\n";
	FuncArray[2].CmpFunc = StrCmp;
	FuncArray[2].OperationFunc = ExitProgram;	
	
	FuncArray[3].str = "<";
	FuncArray[3].CmpFunc = isToFirst;
	FuncArray[3].OperationFunc = AddFirstToFile;
	
	FuncArray[4].str = "";
	FuncArray[4].CmpFunc = AlwaysTrue;
	FuncArray[4].OperationFunc = WriteToFile;	
	
	printf("write here\n");
	

	
	while(TERMINATE_t != ReturnValue)
	{
		fgets(input, 256, stdin);
		
		for(i = 0; i < 5; ++i)
		{
			if( 0 == FuncArray[i].CmpFunc(FuncArray[i].str, input))
			{

				ReturnValue = FuncArray[i].OperationFunc(fp, nameFile, input);
				break;
			}	
		}

	}
	
	FREE(FuncArray);
	FREE(input);
}

int StrCmp(const char* str1, const char* str2)
{ 

int diff = 0;
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
   diff = *str1 - *str2;

   return diff;
}


int isToFirst(const char* str1,const char* str2)
{
	UNUSED(str1);
	return !(*str2 == '<');
}

int AlwaysTrue(const char* str1,const char* str2)
{
	UNUSED(str1);
	UNUSED(str2);
	return 0;
}

/**************************************************/

STATUS_FUNC RemoveFile(FILE* fp, char *FileName, char *input)
{	
	UNUSED(fp);
	UNUSED(input);
	remove(FileName);
	return SUCCESS_t;
}

STATUS_FUNC CountLines(FILE* fp, char *FileName, char *input)
{
	char ch = '0';
	int lines = 0;
	OPENFILE(fp, FileName, "r");
	UNUSED(FileName);
	UNUSED(input);
	
	ch = fgetc(fp);
	while((ch = fgetc(fp)) != EOF)
	{
	  if(ch == '\n')
	  {
	    lines++;
	  }
	}
	printf("%d\n", lines);
	fclose(fp);
	    return SUCCESS_t;
}

STATUS_FUNC ExitProgram(FILE* fp, char *FileName, char *input)
{
	UNUSED(input);
	UNUSED(FileName);
	UNUSED(fp);
    	return TERMINATE_t;
}

STATUS_FUNC AddFirstToFile(FILE* fp, char *FileName, char *input)
{
    FILE *temp_ptr = NULL;
    char ch = '0';
    
    OPENFILE(fp, FileName, "r");
    OPENFILE(temp_ptr, "temporary_file.txt", "a");
    
    fputs(++input, temp_ptr);
    
    while ((ch = fgetc(fp)) != EOF)
    {
        fputc(ch, temp_ptr);
    }
    
    fclose(temp_ptr);
    fclose(fp);
    rename("temporary_file.txt", FileName);

    return SUCCESS_t;	
}

STATUS_FUNC WriteToFile(FILE* fp, char *FileName, char *input)
{
	UNUSED(FileName);
	OPENFILE(fp, FileName, "a");
	fprintf(fp,"%s", input);
	fclose(fp);
	return SUCCESS_t;	
}



