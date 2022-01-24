#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <singly_list.h>
#include <queue.h>
#include <stdatomic.h>
#include <semaphore.h>

volatile int is_message_written;
char *message;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
slist_t *list;
int *a;
const size_t SIZE = 5;
sem_t sema;
sem_t sema2;
slist_iter_t iter;
queue_t *queue;
pthread_cond_t cond;

void single_reader_writer();
void *Reader(void *arg);
void *Writer(void *arg);

void ex2();
void *Reader_ex_2(void *arg);
void *Writer_ex_2(void *arg);

void ex3();
void *Reader_ex_3(void *arg);
void *Writer_ex_3(void *arg);

void ex4();
void *Reader_ex_4(void *arg);
void *Writer_ex_4(void *arg);

void ex5();
void *Reader_ex_5(void *arg);
void *Writer_ex_5(void *arg);

void ex6();
void *Reader_ex_6(void *arg);
void *Writer_ex_6(void *arg);

int main()
{
	/* single_reader_writer(); */
	/* ex2(); */

	/* 	ex3();
	 */
	/* ex4(); */

	/* 	ex5();
	 */
	ex6();
	return 0;
}

void *Reader(void *arg)
{
	(void)arg;
	while (is_message_written)
		;
	fgets(message, 40, stdin);
	is_message_written = 1;
	return NULL;
}

void *Writer(void *arg)
{
	(void)arg;

	while (!is_message_written)
		;
	printf("%s", message);
	is_message_written = 0;
	return NULL;
}

void single_reader_writer()
{
	pthread_t reader, writer;

	message = (char *)malloc(40 * sizeof(*message));
	if (!message)
	{
		return;
	}

	pthread_create(&reader, NULL, Reader, NULL);
	pthread_create(&writer, NULL, Writer, NULL);

	pthread_join(reader, NULL);
	pthread_join(writer, NULL);

	free(message);
}
/* ******************************EX2************************* */
void *Reader_ex_2(void *arg)
{
	size_t i = 0;
	(void)arg;

	pthread_mutex_lock(&mutex);

	for (i = 0; i < SIZE; ++i)
	{
		a[i] = i;
		SListInsert(SListEnd(list), &a[i]);
	}

	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *Writer_ex_2(void *arg)
{
	slist_iter_t iter = SListBegin(list);
	(void)arg;
	pthread_mutex_lock(&mutex);
	while (0 == SListIterIsEqual(iter, SListEnd(list)))
	{
		printf("%d\n", *(int *)SListIterGetData(iter));
		iter = SListIterNext(iter);
	}
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void ex2()
{
	pthread_t reader, writer;

	list = SListCreate();
	a = (int *)malloc(SIZE * sizeof(*a));

	pthread_create(&reader, NULL, Reader_ex_2, NULL);
	pthread_create(&writer, NULL, Writer_ex_2, NULL);

	pthread_join(reader, NULL);
	pthread_join(writer, NULL);

	SListDestroy(list);
	free(a);
}

/* ******************************EX3************************* */

void *Reader_ex_3(void *arg)
{
	(void)arg;

	pthread_mutex_lock(&mutex);

	sem_post(&sema);
	SListInsert(SListEnd(list), arg);

	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *Writer_ex_3(void *arg)
{
	(void)arg;
	pthread_mutex_lock(&mutex);
	sem_wait(&sema);
	printf("%d\n", *(int *)SListIterGetData(iter));
	iter = SListIterNext(iter);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void ex3()
{
	pthread_t reader[5], writer[5];
	size_t i = 0;

	list = SListCreate();
	a = (int *)malloc(SIZE * sizeof(*a));
	sem_init(&sema, 0, 0);
	iter = SListBegin(list);

	for (i = 0; i < SIZE; ++i)
	{
		a[i] = i;
		pthread_create(&reader[i], NULL, Reader_ex_3, &a[i]);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_create(&writer[i], NULL, Writer_ex_3, NULL);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_join(reader[i], NULL);
		pthread_join(writer[i], NULL);
	}
	SListDestroy(list);
	free(a);
}

/* ******************************EX4************************* */

void *Reader_ex_4(void *arg)
{
	(void)arg;
	sem_wait(&sema2);
	pthread_mutex_lock(&mutex);

	sem_post(&sema);
	QueueEnqueue(queue, arg);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *Writer_ex_4(void *arg)
{
	(void)arg;
	sem_wait(&sema);
	pthread_mutex_lock(&mutex);
	sem_post(&sema2);
	printf("%d\n", *(int *)QueuePeek(queue));
	QueueDequeue(queue);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void ex4()
{
	pthread_t reader[5], writer[5];
	size_t i = 0;

	queue = QueueCreate();
	a = (int *)malloc(SIZE * sizeof(*a));
	sem_init(&sema, 0, 0);
	sem_init(&sema2, 0, SIZE);
	for (i = 0; i < SIZE; ++i)
	{
		a[i] = i;

		pthread_create(&reader[i], NULL, Reader_ex_4, &a[i]);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_create(&writer[i], NULL, Writer_ex_4, NULL);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_join(reader[i], NULL);
		pthread_join(writer[i], NULL);
	}
	QueueDestroy(queue);
	free(a);
}

/* ******************************EX5************************* */

void *Reader_ex_5(void *arg)
{
	(void)arg;
	sem_wait(&sema2);

	pthread_mutex_lock(&mutex);

	sem_post(&sema);
	QueueEnqueue(queue, arg);
	pthread_mutex_unlock(&mutex);
	return NULL;
}

void *Writer_ex_5(void *arg)
{
	(void)arg;
	sem_wait(&sema);
	pthread_mutex_lock(&mutex2);
	sem_post(&sema2);
	printf("%d\n", *(int *)QueuePeek(queue));
	QueueDequeue(queue);
	pthread_mutex_unlock(&mutex2);
	return NULL;
}

void ex5()
{
	pthread_t reader[5], writer[5];
	size_t i = 0;

	queue = QueueCreate();
	a = (int *)malloc(SIZE * sizeof(*a));
	sem_init(&sema, 0, 0);
	sem_init(&sema2, 0, SIZE);

	for (i = 0; i < SIZE; ++i)
	{
		a[i] = i;

		pthread_create(&reader[i], NULL, Reader_ex_5, &a[i]);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_create(&writer[i], NULL, Writer_ex_5, NULL);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_join(reader[i], NULL);
		pthread_join(writer[i], NULL);
	}
	QueueDestroy(queue);
	free(a);
}

/* ******************************EX6************************* */

void *Reader_ex_6(void *arg)
{
	(void)arg;

	pthread_mutex_lock(&mutex);

	fgets(message, 40, stdin);
	puts("");
	pthread_mutex_unlock(&mutex);
	pthread_cond_broadcast(&cond);
	return NULL;
}

void *Writer_ex_6(void *arg)
{

	(void)arg;
	pthread_mutex_lock(&mutex2);
	pthread_cond_wait(&cond, &mutex2);
	sem_wait(&sema);
	puts(message);
	pthread_mutex_unlock(&mutex2);
	return NULL;
}

void ex6()
{
	pthread_t reader, writer[5];
	size_t i = 0;
	pthread_cond_init(&cond, NULL);

	message = (char *)malloc(40 * sizeof(*message));
	if (!message)
	{
		return;
	}

	sem_init(&sema, 0, 5);

	pthread_create(&reader, NULL, Reader_ex_6, NULL);

	for (i = 0; i < SIZE; ++i)
	{
		pthread_create(&writer[i], NULL, Writer_ex_6, NULL);
	}

	pthread_join(reader, NULL);

	for (i = 0; i < SIZE; ++i)
	{
		pthread_join(writer[i], NULL);
	}
	pthread_cond_destroy(&cond);
}