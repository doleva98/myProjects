#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "linear_sorts.h"

int main()
{
	int e[5];
	int f[5000];
	int g[5000];

	size_t i;
	const size_t MIN_RANGE = 1;
	const size_t MAX_RANGE = 100;

	srand(time(NULL));

	for (i = 0; i < 5000; ++i)
	{
		e[i] = (rand() % (MAX_RANGE - MIN_RANGE + 1)) + MIN_RANGE;
	}

	CountingSort(e, 5000);

	for (i = 0; i < 5000 - 1; ++i)
	{
		if (e[i] > e[i + 1])
		{
			printf("fail in %d\n", __LINE__);
		}
	}

	for (i = 0; i < 5000; ++i)
	{
		f[i] = (rand() % (10000000 - 1000000 + 1)) + 1000000;
	}

	RadixSort(f, 5000);

	for (i = 0; i < 5000 - 1; ++i)
	{
		if (f[i] > f[i + 1])
		{

			printf("fail in %d\n", __LINE__);
		}
	}

	for (i = 0; i < 5000; ++i)
	{
		g[i] = (rand() % (10000000 - 1000000 + 1)) + 1000000;
	}

	NewRadixSort(g, 5000, 4);

	for (i = 0; i < 5000 - 1; ++i)
	{
		if (g[i] > g[i + 1])
		{

			printf("fail in %d\n", __LINE__);
		}
	}

	return 0;
}