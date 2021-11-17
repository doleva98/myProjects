#include "/home/dolev/git/dolev-arev/include/utils.h"

int CountCouples(char num)
{
	size_t i = 0;
	int count = 0;
	for(; i < 7; ++i)
	{
		if((num & (0x03<<i)) == (0x03<<i))
		{

			++count;
		}
	}
	return count;
}

void Swap1(int *num1, int *num2)
{

	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;

}

void Swap2(int *num1, int *num2)
{

	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;

}

void Swap3(int *num1, int *num2)
{

	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;

}

int CountBitsLong(long num)
{
	
	int count = 0;
	while(num)
	{
		num &= num-1;
		++count;
	}	
	return count;
	
}

int main() {

    char t = 0x33 ;
    int a = 7;
	int b = 10;
	long d = 356;
    printf("%d\n", CountBitsLong(d));
	
	
	Swap3(&a, &b);
	printf("%d", b);
   return 0;
}







