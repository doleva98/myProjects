#include <stdio.h>
#include <limits.h>
long *SumIntPairsToLongs(int a[], size_t size)
{
	size_t i = 0, j = 0;
	long *new_array = (long *)a;

	for (i = 0, j = 0; i < size - 1; ++j, i += 2)
	{
		new_array[j] = (long)((long)a[i] + (long)a[i + 1]);
	}

	return new_array;
}

int main()
{
	int a[6] = {1, 6, 46, -3, INT_MAX, INT_MAX-50};
	long *longs = SumIntPairsToLongs(a, 6);

	printf("%ld\n", longs[0]);
	printf("%ld\n", longs[1]);
		printf("%ld", longs[2]);


	return 0;
}
