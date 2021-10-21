#include "/home/dolev/git/dolev-arev/include/utils.h"
#include "bitwise.h"



int main() {
	int x = 10;
	unsigned int a[] = {56, 7, 8, 2, 274};
	ASSERT(1 == IsPow2Loop(16));
	ASSERT(0 == IsPow2Loop(10));
	ASSERT(1 == IsPow2(16));
	ASSERT(0 == IsPow2(10));
	AddOneNoOpe(&x);
	ASSERT(11 == x);

	OnlyThree(a, sizeof(a) / sizeof(*a));

   return 0;
}

long Pow2(unsigned int x, unsigned int y)
{

	return x*(2^y);

}

int IsPow2(unsigned int n)
{

	return (n!=0) && ((n & (n-1)) == 0);

}

int IsPow2Loop(unsigned int n)
{
	
	unsigned int i = 0;
	unsigned int pow = 1;
	for(; i < n; ++i)
	{
		
		pow = pow << 1;
		if(pow == n)
		{
			return 1;
		}	
		
	}	
	
	return 0;
	
}

void AddOneNoOpe(int *n)
{
	
	int m = 1;
	while(*n & m)
	{
		*n = *n ^ m;
		m = m << 1;
	}
	
	*n = *n ^ m;	
}

void OnlyThree(unsigned int *a, int len)
{
	int i = 0;
	for(; i < len; ++i)
	{
		PrintIsThreeBits(a[i]);
	}
}

void PrintIsThreeBits(int num)
{
	int current = num;
	int counter = 0;
	while(num != 0)
	{
		if(num & 1)
		{
			++counter;
		}
		num >>= 1;
	}
	
	if(counter == 3)
	{
		printf("%d\n", current);
	}
}















