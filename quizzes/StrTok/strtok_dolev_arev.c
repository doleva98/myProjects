#include <stdio.h>

char *Strtok(char *str, const char delim)
{

	static char* s = NULL;
	char *res;
	
	if(str)
	{
		s = str;
	}
	
	if(!s)
	{
		return NULL;
	}
	res = s;
	
	while(*s != delim && *s)
	{

		++s;

	}
	
	if(!*s)
	{
		s =  NULL;
	}
	else{
		*s = '\0';
		++s;
	}
	 
	return res;
	
}

int main()
{
	char str[] = "Hello-world-how-are-youy";
  
	char* token = Strtok(str,  '-');

    while (token != NULL) {
        printf("%s\n", token);
        token = Strtok(NULL, '-');
    }
	

	return 0;
}

