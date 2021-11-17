#include "ws10.h"
#include "stdlib.h"

#define ENDIAN() { \
volatile unsigned long ul = 1;\
volatile unsigned char *p;\
p = (volatile unsigned char *)&ul;\
if (*p == 1)\
puts("Little endian");\
else if (*(p+(sizeof(unsigned long)-1)) == 1)\
puts("Big endian\n");\
else puts("Unknown endian\n");\
}


int main() {

    testItoa10();
   testAtoi10();
   testItoa();
   ENDIAN();
   testThreeChars();
   isLittleEndien();
   testAtoi();
   return 0;
}

void testThreeChars()
{
	char* a = "aaaacc";
   char* b = "ababc";
   char* c = "c";
      ThreeChars(a,b,c);
}

void testAtoi()
{
	char s [] = "100";
	int b;
	b = Atoi(s, 16);
	printf("%d", b);
}

void testItoa()
{
   int b = 4081;
   char p [100];
   Itoa(b,p,16);
	ASSERT(strcmp(p, "FF1")==0);
}

void testAtoi10()
{	
 char z [50] = "-83094";
    int y;

    y = Atoi10(z); 
	
	ASSERT(-83094 == y);
}

void testItoa10()
{
	int x = -130320;
    char s [100];
   
    Itoa10(x,s);
	ASSERT(strcmp("-130320", s) == 0);
}

void Reverse (char *str, int len)
{
	int i = 0;
	char temp;
	
	for(; i < len/2; ++i)
	{
		temp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = temp;
	}
}

char *Itoa10(int value, char *str)
{
	int isNeg = 0;
	char *start = str;
	int countDig = 0;
	if(value == 0)
	{
		*str = '0';
		++str;
		*str = '\0';
		return str;
	}
	if(value < 0)
	{
		isNeg = 1;
		value = -value;
		++countDig;
	}

	while(value)
	{
		sprintf(str, "%d", value % 10);

		value = value / 10;
		++str;
		++countDig;
	}
	
	if(isNeg)
	{
		*str = '-';
		++str;
	}
	
	*str = '\0';
	Reverse(start, countDig);
	return start;
}

int Atoi10(const char *str)
{
	int res = 0;
	int isNeg = 0;
	if(*str == '0')
	{
		return 0;
	}
	
	if(*str == '-')
	{
		isNeg = 1;
		str++;
	}
	
	while(*str != '\0')
	{
		res = res * 10 + *str - '0';	
		++str;
	}
	if(isNeg)
	{
		res = -1 * res;
	}
	return res;
}

char *Itoa(int value, char *str, int base)
{

	int isNeg = 0;
	char *start = str;
	int countDig = 0;
	int lastDig;
	if(value == 0)
	{
		*str = '0';
		++str;
		*str = '\0';
		return str;
	}
	
	if(value < 0 && base == 10)
	{
		isNeg = 1;
		value = -value;
		++countDig;
	}

	while(value)
	{
		lastDig = value % base;

		if(lastDig > 9)
		{
			lastDig = (lastDig - 10) + 'A';	
			sprintf(str, "%c", lastDig);
		}
		else
		{
			sprintf(str, "%d", lastDig);
		}
		value = value / base;
		++str;
		++countDig;
	}

	
	if(isNeg)
	{
		*str = '-';
		++str;
	}
	
	*str = '\0';
	Reverse(start, countDig);
	return start;
}

int toInt(char c)
{
	if(c >= '0' && c <= '9')
	{

		return (int)c - '0';
	}
	else
	{
		return (int)c + 10 - 'A';
	}
}

int Atoi(const char *str, int base)
{
	
	int res = 0;
	int isNeg = 0;
	if(*str == '0')
	{
		return 0;
	}
	
	if(*str == '-')
	{
		isNeg = 1;
		str++;
	}
	
	while(*str)
	{
		res = res*base + toInt(*str);
		++str;
	}
	
	
	if(isNeg)
	{
		res = -1 * res;
	}
	return res;
	
}

void ThreeChars(char* str1, char* str2, char* str3)
{

	int i;
	int letters [128] = {0};
	for(i = 0; str1[i] != '\0'; ++i)
	{
			if(letters[(int)str1[i]] == 0){
				++letters[(int)str1[i]];
			}
		
	}
	for(i = 0; str2[i] != '\0'; ++i)
	{
			if(letters[(int)str2[i]] == 1){
				++letters[(int)str2[i]];
			}
	}
	for(i = 0; str3[i] != '\0'; ++i)
	{
			if(letters[(int)str3[i]] == 2){
				letters[(int)str3[i]] = 0;
			}
	}
	for(i = 0; i < 128; ++i)
	{
		if(letters[i] == 2)
		{
			printf("%c\n", i);
		}
	}
	
}

void isLittleEndien()
{
	int n = 1;
	if(*(char*)&n == 1)
	{
		printf("little endien\n");
	} 
	else
	{
		printf("big endien\n");
	}
}
























