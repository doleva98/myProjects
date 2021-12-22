#include <stdio.h>
#include <stdlib.h>
#include <math.h>
void FindTwoInArray(int *arr, size_t n)
{
	size_t i = 0;
	int xor = arr[0];

	int set_bit;
	int x = 0, y = 0;
	for (i = 1; i < n - 2; ++i)
	{
		xor ^= arr[i];
	}
	for (i = 1; i <= n; ++i)
	{
		xor ^= i;
	}

	set_bit = xor&~(xor-1);

	for (i = 0; i < n - 2; ++i)
	{
		if (arr[i] & set_bit)
		{
			x ^= arr[i];
		}
		else
		{
			y ^= arr[i];
		}
	}
	for (i = 1; i <= n; ++i)
	{
		if (i & set_bit)
		{
			x ^= i;
		}
		else
		{
			y ^= i;
		}
	}
	printf("%d, %d\n", x, y);
}

void FindTwoInArrayWithMath(int *a, size_t n)
{
	size_t i;
	int sum_arr = a[0], prod_arr = a[0];

	int sum_all = 0, prod_all = 1;
	int AandB, AtimeB, AminusB;

	for (i = 1; i < n - 2; ++i)
	{
		sum_arr += a[i];
		prod_arr *= a[i];
	}
	for (i = 1; i <= n; ++i)
	{
		sum_all += i;
		prod_all *= i;
	}
	AandB = sum_all - sum_arr;
	AtimeB = prod_all / prod_arr;

	AminusB = sqrt(pow(AandB, 2) - 4 * AtimeB);
	printf("%d, %d", (AandB + AminusB) / 2, AandB - (AandB + AminusB) / 2);
}

int main()
{
	int arr[3] = {1, 4, 3};
	FindTwoInArray(arr, 5);
	FindTwoInArrayWithMath(arr, 5);
	return 0;
}
