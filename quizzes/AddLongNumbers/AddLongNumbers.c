#include <stdio.h>
#include <stdlib.h>

void AddLongNumbers(const char *num1, const char *num2, char *output);
static void Reverse(char *str);
static size_t Strlen(const char *str);
static int WhoMax(const char *num1, const char *num2);
static char *Strcpy(char *dest, const char *src);

int main()
{
	char *str1 = "1034024325035304";
	char *str2 = "59847584375293148";
	char *output = NULL;

	output = (char *)malloc(100 * sizeof(char));
	if (!output)
	{
		fprintf(stderr, "OUT OF MEM");
		return 0;
	}

	AddLongNumbers(str1, str2, output);
	printf("%s\n", output);
	free(output);
	return 0;
}

void AddLongNumbers(const char *num1, const char *num2, char *output)
{
	int carry = 0, sum = 0;
	size_t i = 0;
	int isNum1Max = WhoMax(num1, num2);
	size_t lower_len = Strlen(num1);
	size_t higher_len = Strlen(num2), temp;
	char *str1 = NULL;
	char *str2 = NULL;
	char *max = NULL;

	str1 = (char *)malloc(100 * sizeof(char));
	if (!str1)
	{
		fprintf(stderr, "OUT OF MEM");
		return;
	}

	str2 = (char *)malloc(100 * sizeof(char));
	if (!str2)
	{
		fprintf(stderr, "OUT OF MEM");
		return;
	}

	Strcpy(str1, num1);
	Strcpy(str2, num2);

	if (isNum1Max)
	{
		temp = lower_len;
		lower_len = higher_len;
		higher_len = temp;
	}
	Reverse(str1);
	Reverse(str2);

	for (; i < lower_len; ++i)
	{
		sum = (str1[i] - '0') + (str2[i] - '0') + carry;
		output[i] = sum % 10 + '0';
		carry = sum / 10;
	}

	max = str2;

	if (isNum1Max)
	{
		max = str1;
	}

	for (; i < higher_len; ++i)
	{
		sum = (max[i] - '0') + carry;
		output[i] = sum % 10 + '0';
		carry = sum / 10;
	}

	if (carry)
	{
		output[i] = carry + '0';
	}
	output[i] = '\0';

	Reverse(output);

	++i;
	free(str1);
	free(str2);
}

static int WhoMax(const char *num1, const char *num2)
{
	return Strlen(num1) > Strlen(num2);
}

static size_t Strlen(const char *str)
{
	size_t size = 0;
	while (*str)
	{
		++size;
		++str;
	}
	return size;
}

static void Reverse(char *str)
{
	size_t i = 0;
	size_t size = Strlen(str);
	char temp;
	for (; i < size / 2; ++i)
	{
		temp = str[i];
		str[i] = str[size - i - 1];
		str[size - i - 1] = temp;
	}
}

static char *Strcpy(char *dest, const char *src)
{
	while (*src)
	{
		*dest = *src;
		++src;
		++dest;
	}
	*dest = '\0';
	return dest;
}