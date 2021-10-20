typedef enum {SUCCESS_t, TERMINATE_t}STATUS_FUNC; 

void ex1();
void Print(int i);
void Logger(char *nameFile);
int StrCmp(const char* str1, const char* str2);
int isToFirst(const char* str1, const char* str2);
int AlwaysTrue(const char* str1,const char* str2);

STATUS_FUNC RemoveFile(FILE* fp, char *FileName, char *input);
STATUS_FUNC CountLines(FILE* fp, char *FileName, char *input);
STATUS_FUNC ExitProgram(FILE* fp, char *FileName, char *input);
STATUS_FUNC AddFirstToFile(FILE* fp, char *FileName, char *input);
STATUS_FUNC WriteToFile(FILE* fp, char *FileName, char *input);


typedef struct 
	{	
		char *str;
		int (*CmpFunc)(const char*,const char*);
		STATUS_FUNC (*OperationFunc)(FILE*, char*, char*);	
	}funcLogger_t;


