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

void single_Producer_Consumer();
void *Producer(void *arg);
void *Consumer(void *arg);

void ex2();
void *Producer_ex_2(void *arg);
void *Consumer_ex_2(void *arg);

void ex3();
void *Producer_ex_3(void *arg);
void *Consumer_ex_3(void *arg);

void ex4();
void *Producer_ex_4(void *arg);
void *Consumer_ex_4(void *arg);

void ex5();
void *Producer_ex_5(void *arg);
void *Consumer_ex_5(void *arg);

void ex6();
void *Producer_ex_6(void *arg);
void *Consumer_ex_6(void *arg);

int main()
{
	/* single_Producer_Consumer(); */
	/* ex2(); */

	/* 	ex3();
	 */
	/* 	ex4();
	 */
	/* 	ex5();
	 */
	ex6();
	return 0;
}

void *Producer_ex_1(void *arg)
{
	(void)arg;
	while (is_message_written)
		;
	fgets(message, 40, stdin);
	is_message_written = 1;
	return NULL;
}

void *Consumer_ex_1(void *arg)
{
	(void)arg;

	while (!is_message_written)
		;
	printf("%s", message);
	is_message_written = 0;
	return NULL;
}

void single_Producer_Consumer()
{
	pthread_t Producer, Consumer;

	message = (char *)malloc(40 * sizeof(*message));
	if (!message)
	{
		return;
	}

	pthread_create(&Producer, NULL, Producer_ex_1, NULL);
	pthread_create(&Consumer, NULL, Consumer_ex_1, NULL);

	pthread_join(Producer, NULL);
	pthread_join(Consumer, NULL);

	free(message);
}
/* ******************************EX2************************* */
void *Producer_ex_2(void *arg)
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

void *Consumer_ex_2(void *arg)
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
	pthread_t Producer, Consumer;

	list = SListCreate();
	if (!list)
	{
		return;
	}
	a = (int *)malloc(SIZE * sizeof(*a));
	if (!a)
	{
		return;
	}

	pthread_create(&Producer, NULL, Producer_ex_2, NULL);
	pthread_create(&Consumer, NULL, Consumer_ex_2, NULL);

	pthread_join(Producer, NULL);
	pthread_join(Consumer, NULL);

	SListDestroy(list);
	free(a);
}

/* ******************************EX3************************* */

void *Producer_ex_3(void *arg)
{
	size_t i = 0;
	(void)arg;
	for (i = 0; i < 5; ++i)
	{
		pthread_mutex_lock(&mutex);

		SListInsert(SListEnd(list), arg);

		pthread_mutex_unlock(&mutex);

		sem_post(&sema);
	}
	return NULL;
}

void *Consumer_ex_3(void *arg)
{
	int data = 0;
	/* 	size_t i = 0;
	 */
	(void)arg;
	while (1)
	{
		sem_wait(&sema);

		pthread_mutex_lock(&mutex);
		data = *(int *)SListIterGetData(iter);
		iter = SListIterNext(iter);
		printf("%d\n", data);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void ex3()
{
	pthread_t Producer[5], Consumer[5];
	size_t i = 0;

	list = SListCreate();
	if (!list)
	{
		return;
	}

	a = (int *)malloc(SIZE * sizeof(*a));
	if (!a)
	{
		return;
	}

	sem_init(&sema, 0, 0);
	iter = SListBegin(list);

	for (i = 0; i < SIZE; ++i)
	{
		a[i] = i;
		pthread_create(&Producer[i], NULL, Producer_ex_3, &a[i]);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_create(&Consumer[i], NULL, Consumer_ex_3, NULL);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_join(Producer[i], NULL);
		pthread_join(Consumer[i], NULL);
	}
	SListDestroy(list);
	sem_destroy(&sema);
	free(a);
}

/* ******************************EX4************************* */

void *Producer_ex_4(void *arg)
{
	size_t i = 0;
	(void)arg;
	for (i = 0; i < 5; ++i)
	{
		sem_wait(&sema2);

		pthread_mutex_lock(&mutex);
		QueueEnqueue(queue, arg);
		pthread_mutex_unlock(&mutex);
		sem_post(&sema);
	}
	return NULL;
}

void *Consumer_ex_4(void *arg)
{
	(void)arg;
	while (1)
	{
		sem_wait(&sema);
		pthread_mutex_lock(&mutex);
		printf("%d\n", *(int *)QueuePeek(queue));
		QueueDequeue(queue);
		pthread_mutex_unlock(&mutex);
		sem_post(&sema2);
	}
	return NULL;
}

void ex4()
{
	pthread_t Producer[5], Consumer[5];
	size_t i = 0;

	queue = QueueCreate();
	a = (int *)malloc(SIZE * sizeof(*a));
	if (!a)
	{
		return;
	}
	sem_init(&sema, 0, 0);
	sem_init(&sema2, 0, SIZE);
	for (i = 0; i < SIZE; ++i)
	{
		a[i] = i;

		pthread_create(&Producer[i], NULL, Producer_ex_4, &a[i]);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_create(&Consumer[i], NULL, Consumer_ex_4, NULL);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_join(Producer[i], NULL);
		pthread_join(Consumer[i], NULL);
	}
	QueueDestroy(queue);
	free(a);
}

/* ******************************EX5************************* */

void *Producer_ex_5(void *arg)
{
	(void)arg;
	sem_wait(&sema2);

	pthread_mutex_lock(&mutex);

	QueueEnqueue(queue, arg);
	pthread_mutex_unlock(&mutex);
	sem_post(&sema);
	return NULL;
}

void *Consumer_ex_5(void *arg)
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
	pthread_t Producer[5], Consumer[5];
	size_t i = 0;

	queue = QueueCreate();
	a = (int *)malloc(SIZE * sizeof(*a));
	if (!a)
	{
		return;
	}
	sem_init(&sema, 0, 0);
	sem_init(&sema2, 0, SIZE);

	for (i = 0; i < SIZE; ++i)
	{
		a[i] = i;

		pthread_create(&Producer[i], NULL, Producer_ex_5, &a[i]);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_create(&Consumer[i], NULL, Consumer_ex_5, NULL);
	}

	for (i = 0; i < SIZE; ++i)
	{
		pthread_join(Producer[i], NULL);
		pthread_join(Consumer[i], NULL);
	}
	QueueDestroy(queue);
	free(a);
}

/* ******************************EX6************************* */
void *Producer_ex_6(void *arg)
{
	(void)arg;
	pthread_mutex_lock(&mutex);
	fgets(message, 40, stdin);
	puts("");
	pthread_mutex_unlock(&mutex);
	pthread_cond_broadcast(&cond);
	return NULL;
}
void *Consumer_ex_6(void *arg)
{
	(void)arg;
	sem_wait(&sema);
	pthread_mutex_lock(&mutex2);
	pthread_cond_wait(&cond, &mutex2);
	printf("%s", message);
	pthread_mutex_unlock(&mutex2);
	return NULL;
}
void ex6()
{
	pthread_t Producer, Consumer[5];
	size_t i = 0;

	pthread_cond_init(&cond, NULL);
	message = (char *)malloc(40 * sizeof(*message));
	if (!message)
	{
		return;
	}
	sem_init(&sema, 0, 5);
	pthread_create(&Producer, NULL, Producer_ex_6, NULL);
	for (i = 0; i < SIZE; ++i)
	{
		pthread_create(&Consumer[i], NULL, Consumer_ex_6, NULL);
	}
	pthread_join(Producer, NULL);
	for (i = 0; i < SIZE; ++i)
	{
		pthread_join(Consumer[i], NULL);
	}
	free(message);
	pthread_cond_destroy(&cond);
}
