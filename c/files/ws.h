void ex1();
void Print(int i);
void Logger(char *nameFile);
int StrCmp(const char* str1, const char* str2);
int isToFirst(const char* str1, const char* str2);

typedef enum {SUCCESS_t, FAIL_t}STATUS_FUNC; 

STATUS_FUNC RemoveFile(FILE* fp, char *FileName, char *input);
STATUS_FUNC CountLines(FILE* fp, char *FileName, char *input);
STATUS_FUNC ExitProgram(FILE* fp, char *FileName, char *input);
STATUS_FUNC AddFirstToFile(FILE* fp, char *FileName, char *input);
STATUS_FUNC WriteToFile(FILE* fp, char *FileName, char *input);
int HowManyLines(FILE* fp);
int AlwaysTrue(const char* str1, const char* str2);
