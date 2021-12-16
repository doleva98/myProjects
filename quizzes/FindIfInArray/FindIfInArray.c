#include <stdio.h>

int FindIfInArray(int *arr, int n, size_t len)
{
	size_t i = 0;
	size_t sum = 0;

	for (i = 0; i < len; ++i)
	{
		sum += !!(arr[i] ^ n);
	}
	return sum != len;
}

int main()
{
	int arr[5] = {4, 6, 8, 44, 3};
	printf("%d", FindIfInArray(arr, 6, 5));

	return 0;
}
