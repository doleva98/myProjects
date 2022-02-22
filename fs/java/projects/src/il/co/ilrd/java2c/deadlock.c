#include <stdio.h>
#include <pthread.h>

void *foo(void *a);
void *foo2(void *a);
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;

int main()
{

    pthread_t threads[2];
    pthread_mutex_init(&mutex1, NULL);
    pthread_mutex_init(&mutex2, NULL);
    pthread_create(&threads[0], NULL, foo, NULL);
    pthread_create(&threads[1], NULL, foo2, NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    pthread_mutex_destroy(&mutex1);
    pthread_mutex_destroy(&mutex2);

    return 0;
}

void *foo(void *a)
{

    pthread_mutex_lock(&mutex1);
    sleep(1);

    pthread_mutex_lock(&mutex2);

    printf("hello");

    pthread_mutex_unlock(&mutex1);

    pthread_mutex_unlock(&mutex2);

    return NULL;
}

void *foo2(void *a)
{
    pthread_mutex_lock(&mutex2);
    sleep(1);
    pthread_mutex_lock(&mutex1);

    printf("hello");

    pthread_mutex_unlock(&mutex2);
    pthread_mutex_unlock(&mutex1);
}