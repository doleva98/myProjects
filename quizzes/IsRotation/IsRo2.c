#include "/home/dolev/git/dolev-arev/include/utils.h"

int IsRo(char* str1, char* str2)
{
	size_t source = 0;
	size_t check = 0;

	
	if(strlen(str1) != strlen(str2))
	{
		return 0;
	}
	
	
	for(; check < 2*strlen(str1); ++check)
	{
		if(str1[source] == str2[check%strlen(str1)])
		{

			++source;	
			if(source == strlen(str1))
			{
				return 1;
			}	
		}
		
		else
		{

			source = 0;
		}
	}
	return 0;
}

int main() {
char *a = "   h*e ll wowo";
char *b = "h*e ll w   owo   ";
printf("%d", IsRo(a,b));
    

   return 0;
}

