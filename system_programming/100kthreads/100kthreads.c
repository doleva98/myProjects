#define _GNU_SOURCE
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static void *ThreaFunc(void *arg);
int arr[100000];

static void ex1();

int main()
{
	ex1();
	return 0;
}

static void ex1()
{
	pthread_t threads[50000];
	size_t i = 0;

	for (i = 0; i < 50000; ++i)
	{
		pthread_create(&threads[i], NULL, ThreaFunc, &i);
		pthread_detach(threads[i]);
	}

	sleep(10);
	if (5000 != arr[5000])
	{
		printf("fail in %d\n", __LINE__);
	}
	for (i = 0; i < 1000; ++i)
	{
		if ((int)i != arr[i])
		{
			printf("i is %ld and arr[%ld] is %d\n", i, i, arr[i]);
			printf("fail in %d\n", __LINE__);
		}
	}
}

static void *ThreaFunc(void *arg)
{
	int num = *(int *)arg;
	arr[num] = num;
	return NULL;
}