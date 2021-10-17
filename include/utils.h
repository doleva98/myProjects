#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_PINK    "\x1b[95m"
#define ANSI_COLOR_BRIGHT_BLUE    "\x1b[36m"
#define ANSI_COLOR_BLUE    "\x1b[34m"

#define ASSERT(expr) \
do\
{ \
    	if (!(expr)) \
        aFailed(__FILE__, __LINE__); \
} while(0)

#define FREE(ptr) \
do \
{ \
	free(ptr); \
	ptr = NULL; \
} while(0)
        
void aFailed(char *file, int line){
	printf(ANSI_COLOR_RED "\nFAIL in line %d, in file %s\n" ANSI_COLOR_RESET, line, file);
}    
