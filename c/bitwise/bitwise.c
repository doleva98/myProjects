#include "bitwise.h"

int main()
{
	int x = 10;
	unsigned int a[] = {56, 7, 8, 2, 274};
	int c = 10;
	int d = 55;
	float f = 7.9888568;
	ASSERT(1 == IsPow2Loop(16));
	ASSERT(0 == IsPow2Loop(10));
	ASSERT(1 == IsPow2(16));
	ASSERT(0 == IsPow2(10));
	AddOneNoOpe(&x);
	ASSERT(11 == x);

	OnlyThree(a, sizeof(a) / sizeof(*a));
	ASSERT(210 == ByteMirrorLoop(75));

	ASSERT(210 == ByteMirror(75));
	ASSERT(1 == IsSecondAndSixth(162));
	ASSERT(0 == IsSecondAndSixth(0));
	ASSERT(1 == IsSecondAndSixth(0x22));
	ASSERT(0 == IsSecondAndSixth(0x00));

	ASSERT(1 == IsAtLeastSecondAndSixth(2));
	ASSERT(1 == IsAtLeastSecondAndSixth(0x20));
	ASSERT(0 == IsAtLeastSecondAndSixth(0x88));

	ASSERT(0x10 == SwapThirdAndFifth(0x04));
	ASSERT(16 == ClosestDeviseAbleBy16(31));
	ASSERT(32 == ClosestDeviseAbleBy16(33));

	SwapWithtoutTemp(&c, &d);
	ASSERT(55 == c);

	ASSERT(3 == CountWithLoop(7));
	ASSERT(1 == CountWithLoop(16));

	ASSERT(3 == CountNoLoop(7));
	ASSERT(1 == CountNoLoop(16));

	PrintBitsFLoat(&f);

	return 0;
}

long Pow2(unsigned int x, unsigned int y)
{

	return x * (2 ^ y);
}

int IsPow2(unsigned int n)
{
	return (n != 0) && ((n & (n - 1)) == 0); /* you should use only bit operation */
}

int IsPow2Loop(unsigned int n)
{

	unsigned int i = 0;
	unsigned int pow = 1;
	for (; i < n; ++i)
	{

		pow = pow << 1;
		if (pow == n)
		{
			return 1;
		}
	}

	return 0;
}

void AddOneNoOpe(int *n)
{

	int m = 1;
	while (*n & m)
	{
		*n = *n ^ m;
		m = m << 1;
	}

	*n = *n ^ m;
}

void OnlyThree(unsigned int *a, int len)
{
	int i = 0;
	for (; i < len; ++i)
	{
		PrintIsThreeBits(a[i]);
	}
}

void PrintIsThreeBits(int num)
{
	int current = num;
	int counter = 0;
	while (num != 0)
	{
		if (num & 1)
		{
			++counter;
		}
		num >>= 1;
	}

	if (counter == 3)
	{
		printf("%d\n", current);
	}
}

unsigned char ByteMirrorLoop(unsigned char num)
{
	char result = 0;
	int i = 0;
	for (; i < 8; ++i)
	{
		result = result | (1 & num);
		if (i < 7)
		{
			result <<= 1;
			num >>= 1;
		}
	}
	return result;
}

unsigned char ByteMirror(unsigned char b)
{
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

int IsSecondAndSixth(unsigned char num)
{
	unsigned char result = num & 0x22;
	return result == 0x22;
}

int IsAtLeastSecondAndSixth(unsigned char num)
{
	unsigned char result = num & 0x22;
	return result == 0x02 || result == 0x20;
}

unsigned char SwapThirdAndFifth(unsigned char num)
{

	unsigned char result = num & 0xEB;
	unsigned char ThirdBit = num & 4;
	unsigned char FifthBit = num & 0x10;
	ThirdBit = ThirdBit << 2;
	FifthBit = FifthBit >> 2;

	result = result | ThirdBit;
	result = result | FifthBit;
	return result;
}

unsigned int ClosestDeviseAbleBy16(unsigned int num)
{
	for (; num > 0; --num)
	{
		if (num % 16 == 0)
		{
			return num;
		}
	}
	return 0;
}

void SwapWithtoutTemp(int *num1, int *num2)
{
	if (*num1 != *num2)
	{
		*num1 = *num1 ^ *num2;
		*num2 = *num1 ^ *num2;
		*num1 = *num1 ^ *num2;
	}
}

unsigned int CountWithLoop(unsigned int num)
{
	int count = 0;
	while (num != 0)
	{
		if (num & 1)
		{
			++count;
		}
		num >>= 1;
	}
	return count;
}

unsigned int CountNoLoop(unsigned int n)
{

	n = ((n & 0xAAAAAAAA) >> 1) + (n & 0x55555555);
	n = ((n & 0xCCCCCCCC) >> 2) + (n & 0x33333333);
	n = ((n & 0xF0F0F0F0) >> 4) + (n & 0x0F0F0F0F);
	n = ((n & 0xFF00FF00) >> 8) + (n & 0x00FF00FF);
	n = ((n & 0xFFFF0000) >> 16) + (n & 0x0000FFFF);
	return n;
}

void PrintBitsFLoat(float *num)
{
	int i = 31;
	int *temp = (int *)num;

	for (; i >= 0; --i)
	{
		printf("%d", IsBit(*temp, i));
	}
}

int IsBit(int a, int loc)
{
	int buf = a & (1 << loc);
	return !(buf == 0);
}
