#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vsa.h"

int main()
{
	const size_t SIZE = 500;
		
	void *pool = NULL;
	var_alloc_t *vsa = NULL;
	
	char *test1 = NULL;
	char *test2 = NULL;
	char *test3 = NULL;
	char *test4 = NULL;
	
	pool = malloc(SIZE);
	vsa = VSAInit(pool, SIZE);
	printf("Free space: %lu\n", LargestChunkAvailable(vsa));
	test1 = VSAAlloc(vsa, 1);
	printf("Free space: %lu\n", LargestChunkAvailable(vsa));
	*test1 = 'a';
	test2 = VSAAlloc(vsa, 1);
	*test2 = 'D';
	test3 = VSAAlloc(vsa, 100);
	test4 = VSAAlloc(vsa, 200);
	strcat(test3, "Hello World!");
	printf("%s\n", test3);
	printf("Free space: %lu\n", LargestChunkAvailable(vsa));
	VSAFree(test3);
	printf("Free space: %lu\n", LargestChunkAvailable(vsa));
	VSAFree(test2);
	printf("Free space: %lu\n", LargestChunkAvailable(vsa));
	free(pool);
	return 0;
}
