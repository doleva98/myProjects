#include <stdio.h>

int MaxStolenVal(int *val, int *wt, size_t N, int max_w);

int main()
{
	int val[] = {10, 40, 30, 50};
	int wt[] = {5, 4, 6, 3};
	printf("%d", MaxStolenVal(val, wt, sizeof(val) / sizeof(*val), 10));
	return 0;
}

int Max(int a, int b)
{
	return a > b ? a : b;
}

int MaxStolenVal(int *val, int *wt, size_t N, int max_w)
{
	if (0 == N || 0 == max_w)
	{
		return 0;
	}

	if (wt[N - 1] > max_w)
	{
		return MaxStolenVal(val, wt, N - 1, max_w);
	}
	else
	{
		return Max(val[N - 1] + MaxStolenVal(val, wt, N - 1, max_w - wt[N - 1]),
				   MaxStolenVal(val, wt, N - 1, max_w));
	}
}