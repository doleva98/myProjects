#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
static int FlipDigitsNum(int n);
unsigned char Mirror(unsigned char n);
unsigned char MirrornoLoop(unsigned char n);
unsigned int FlipBit(unsigned int val, unsigned int n);
int CountOn(unsigned char n);
int popcnt8(unsigned char x);
unsigned char RotateLeft(unsigned char byte, unsigned int nbits);
void swap(int **p1, int **p2);
size_t Strlen(const char *s);
int Strcmp(const char *s1, const char *s2);
char *Strcpy(char *dest, const char *src);
char *Strncpy(char *dest, const char *src, size_t n);
char *Strcat(char *dest, const char *src);
unsigned long GetFibNum(unsigned int n);
char *IntToString(int n, char *str);
unsigned int MultBy8(unsigned int n);
void WhatSize();

int main()
{
	int test1 = 6;
	int test2 = 90;
	int *p1 = &test1;
	int *p2 = &test2;
	char str1[100];
	char str2[100];
	char *str3 = malloc(100);
	if (!str3)
	{
		fprintf(stderr, "OUT OF MEMORY");
		exit(1);
	}
	if (!(-58 == FlipDigitsNum(-85)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(0 == FlipDigitsNum(0)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(518 == FlipDigitsNum(815)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(192 == Mirror(3)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(192 == MirrornoLoop(3)))
	{
		printf("fail in %d\n", __LINE__);
	}
	if (!(2 == FlipBit(3, 0)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(200 == FlipBit(192, 3)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(2 == CountOn(3)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(2 == popcnt8(3)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(12 == RotateLeft(3, 2)))
	{
		printf("fail in %d\n", __LINE__);
	}

	swap(&p1, &p2);
	if (!(90 == *p1))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(Strlen("Hello world!!!") == strlen("Hello world!!!")))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(strcmp("Za", "Za") == Strcmp("Za", "Za")))
	{
		printf("fail in %d\n", __LINE__);
	}

	Strcpy(str1, "Hello world!");

	if (!(Strcmp(str1, "Hello world!") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	Strncpy(str2, "Dumbeldore", 5);

	if (!(Strcmp(str2, "Dumbe") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	Strcat(str1, str2);

	if (!(Strcmp(str1, "Hello world!Dumbe") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(GetFibNum(8) == 21))
	{
		printf("fail in %d\n", __LINE__);
	}
	IntToString(-432, str1);
	if (!(Strcmp(str1, "-432") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(MultBy8(8) == 64))
	{
		printf("fail in %d\n", __LINE__);
	}

	WhatSize();

	return 0;
}

static int FlipDigitsNum(int n)
{
	int isNeg = 1;
	int res = 0;
	if (n < 0)
	{
		isNeg = -1;
		n *= -1;
	}

	while (n)
	{
		res = res * 10 + n % 10;
		n /= 10;
	}
	return isNeg * res;
}

unsigned char Mirror(unsigned char n)
{
	unsigned char result = 0;
	int i = 0;
	for (; i < 8; ++i)
	{
		result = result | (1 & n);
		if (i < 7)
		{
			result <<= 1;
			n >>= 1;
		}
	}
	return result;
}

unsigned char MirrornoLoop(unsigned char n)
{
	n = (n & 0xF0) >> 4 | (n & 0x0F) << 4;
	n = (n & 0xCC) >> 2 | (n & 0x33) << 2;
	n = (n & 0xAA) >> 1 | (n & 0x55) << 1;
	return n;
}

unsigned int FlipBit(unsigned int val, unsigned int n)
{
	unsigned int pos = 0;
	pos |= ((1 << n) & val) >> n;
	val &= ~(1 << n);
	if (!pos)
	{
		val |= 1 << n;
	}
	return val;
}

int CountOn(unsigned char n)
{
	int i = 0;
	int count = 0;

	for (; i < 8; ++i)
	{
		count += (n >> i) & 1;
	}
	return count;
}

int popcnt8(unsigned char x)
{

	x = (x & 0x55) + (x >> 1 & 0x55);
	x = (x & 0x33) + (x >> 2 & 0x33);
	x = (x & 0x0f) + (x >> 4 & 0x0f);
	return x;
}

unsigned char RotateLeft(unsigned char byte, unsigned int nbits)
{
	unsigned int i = 0;
	unsigned char temp = 0;
	nbits %= 8;

	for (; i < nbits; ++i)
	{
		temp = ((1 << 7) & byte) >> 7;
		byte <<= 1;
		byte |= temp;
	}
	return byte;
}

void swap(int **p1, int **p2)
{
	int *temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}
size_t Strlen(const char *s)
{
	size_t count = 0;
	assert(s);
	while (*s)
	{
		++count;
		++s;
	}
	return count;
}

int Strcmp(const char *s1, const char *s2)
{
	assert(s1 && s2);
	while (*s1)
	{
		if (*s1 != *s2)
		{
			break;
		}
		++s1;
		++s2;
	}
	return *s1 - *s2;
}

char *Strcpy(char *dest, const char *src)
{
	assert(dest && src);

	while (*src)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	return dest;
}

char *Strncpy(char *dest, const char *src, size_t n)
{
	assert(dest && src);

	while (*src && n)
	{
		*dest = *src;
		++dest;
		++src;
		--n;
	}
	*dest = '\0';
	return dest;
}

char *Strcat(char *dest, const char *src)
{
	char *start = dest;
	assert(dest && src);
	while (*dest)
	{
		++dest;
	}
	Strcpy(dest, src);
	return start;
}

unsigned long GetFibNum(unsigned int n)
{
	assert(n > 0);
	if (n == 1 || n == 2)
	{
		return 1;
	}
	return GetFibNum(n - 1) + GetFibNum(n - 2);
}

char *IntToString(int n, char *str)
{
	sprintf(str, "%d", n);
	while (*str)
	{
		++str;
	}
	*str = '\0';
	return str;
}

unsigned int MultBy8(unsigned int n)
{
	return n << 3;
}

void WhatSize()
{
	char *s1 = "hello";
	char s2[] = "hello";
	size_t a[] = {1, 2, 4, 5};
	size_t val = 3;
	union
	{
		char a[7];
		int i;
		short s;
	} jack;
	printf("%lu, %lu, %lu jack is %lu\n", sizeof(s1), sizeof(s2), val[a], sizeof(jack));
}
