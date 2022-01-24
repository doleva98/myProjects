#include <stdio.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>	/* O_CREAT */
#include <stdlib.h> /* for exit */
#include <assert.h>

/* code reviewed by daniel */
int main(int argc, char **argv)
{

	int COUNTER = 2;

	sem_t *sema;
	size_t i = 0;
	int counter = 0;

	assert(argv[2]);

	sema = sem_open(argv[1], O_CREAT, 0666, COUNTER);

	if ('D' == argv[2][0])
	{
		for (i = 0; i < (size_t)atoi(argv[3]); ++i)
		{
			sem_wait(sema);
		}
	}

	if ('I' == argv[2][0])
	{
		for (i = 0; i < (size_t)atoi(argv[3]); ++i)
		{
			sem_post(sema);
		}
	}

	if ('V' == argv[2][0])
	{
		sem_getvalue(sema, &counter);
		printf("the value is %d", counter);
	}

	if ('X' == argv[2][0])
	{
		sem_close(sema);
		sem_unlink(argv[1]);
	}

	return 0;
}
