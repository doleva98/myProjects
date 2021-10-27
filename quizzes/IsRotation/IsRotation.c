#include "/home/dolev/git/dolev-arev/include/utils.h"

void RotateRight(char* str, int len)
{
	int i = len-1;
	char last = str[i];
	for(; i > 0; --i)
	{
		str[i] = str[i-1];
	}
	str[i] = last;
}

int IsRotation(char* str1, int len1, char* str2, int len2)
{
	int i = 0;
	int istrue = 0;
	if(len1 != len2)
	{
		return 0;
	}
	
	for(; i < len2; ++i)
	{
		if(strcmp(str1, str2) == 0)
		{
			istrue = 1;
		}
		RotateRight(str2, len2);
	}
	return istrue;
	
}

int main() {

    char a [] = "He  ll ob";
    char b [] = "bHe  ll o";

	printf("%d\n", IsRotation(a, strlen(a), b, strlen(b)));

   return 0;
}
