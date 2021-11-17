#include <stdio.h>


unsigned int plusone(unsigned int n)
{
	int m = 1;
	while(n & m)
	{
		n ^= m;
		m  <<= 1;
	}
	
	n ^= m;
	return n;	
}

int main()
{

	printf("%u", plusone(18));	

	return 0;
}
