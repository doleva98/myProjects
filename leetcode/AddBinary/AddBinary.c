#include <stdio.h>
#include <stdlib.h>
static size_t Strlen(char *str);
static void Reverse(char *str);
char *addBinary(char *a, char *b);

int main()
{
	char a[100] = "0";
	char b[100] = "1";
	char *str = addBinary(a, b);
	puts(str);
	free(str);
	return 0;
}

char *addBinary(char *a, char *b)
{
	size_t len1 = Strlen(a);
	size_t len2 = Strlen(b);
	size_t max_size = len2;
	size_t short_size = len1;
	char *max = NULL;
	size_t i = 0;
	int sum = 0, carry = 0;
	char *output = NULL;

	output = (char *)malloc(100);
	if (!output)
	{
		return NULL;
	}

	if (len1 > len2)
	{
		max_size = len1;
		short_size = len2;
	}
	Reverse(a);
	Reverse(b);
	for (; i < short_size; ++i)
	{
		sum = (a[i] - '0') + (b[i] - '0') + carry;
		output[i] = (sum % 2) + '0';
		carry = sum / 2;
	}
	max = b;
	if (max_size == len1)
	{
		max = a;
	}
	for (; i < max_size; ++i)
	{
		sum = (max[i] - '0') + carry;
		output[i] = (sum % 2) + '0' ;
		carry = sum / 2;
	}
	if (carry)
	{
		output[i] = carry + '0';
	}
	++i;
	output[i] = '\0';
	Reverse(output);
	return output;
}

static void Reverse(char *str)
{
	size_t i = 0;
	size_t size = Strlen(str);
	char temp;
	for (; i < size / 2; i++)
	{
		temp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = temp;
	}
}

static size_t Strlen(char *str)
{
	size_t count = 0;
	while (*str)
	{
		++count;
		++str;
	}
	return count;
}
