#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Reverse(char *begin, char *end)
{
	char temp;
	while (begin < end)
	{
		temp = *begin;
		*begin++ = *end;
		*end-- = temp;
	}
}

char *ReverseWords(char *str)
{
	char *word_begin = str;
	char *temp = str;

	/*reverse individual words*/

	while (*temp)
	{
		++temp;
		if (!*temp)
		{
			Reverse(word_begin, temp - 1);
		}
		else if (*temp == ' ')
		{
			Reverse(word_begin, temp - 1);
			word_begin = temp + 1;
		}
	}
	Reverse(str, temp - 1);
	return str;
}

int main()
{
	char str[] = "i am student";
	puts(ReverseWords(str));
	return 0;
}
