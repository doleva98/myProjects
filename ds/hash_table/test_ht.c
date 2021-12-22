#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ht.h"

static void test1();
static void test2();
static size_t hash_func_words(const void *new_elem);
static int same_word(void *data, void *param);

int main()
{
	test1();
	test2();
	return 0;
}
static void test2()
{
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t num_words = 102401;
	char *str[102401];
	char input[100];
	hash_t *ht = NULL;
	size_t size = 100000;
	size_t i = 0;

	ht = HashCreate(hash_func_words, same_word, size);

	if (!(HashSize(ht) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (0 == HashIsEmpty(ht))
	{
		printf("fail in %d\n", __LINE__);
	}

	fp = fopen("/usr/share/dict/words", "r");
	if (fp == NULL)
	{
		exit(EXIT_FAILURE);
	}

	for (i = 0; getline(&line, &len, fp) != -1; ++i)
	{
		str[i] = strdup(line);
		HashInsert(ht, str[i]);
	}

	if (!HashFind(ht, "zoo\n"))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(strcmp(HashFind(ht, "zoo\n"), "zoo\n") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HashIsEmpty(ht))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(HashSize(ht) == (size_t)num_words))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HashFind(ht, "wow"))
	{
		printf("fail in %d\n", __LINE__);
	}

	printf("\033[0;35m");
	printf("please enter a word to check if in dictionary\n");
	printf("\033[0m");

	scanf("%s", input);
	strcat(input, "\n");
	while (strcmp(input, "exit\n") != 0)
	{
		if (HashFind(ht, input))
		{
			printf("\033[0;32m");
			printf("THAT WAS A WORD IN THE DICTIONARY\n");
			printf("\033[0m");
		}
		else
		{
			printf("\033[0;31m");
			printf("NO, I AM SORRY BUT IT IS NOT IN THE DICTIONARY\n");
			printf("\033[0m");
		}
		scanf("%s", input);
		strcat(input, "\n");
	}

	fclose(fp);
	if (line)
	{
		free(line);
	}

	for (i = 0; (ssize_t)i < num_words; ++i)
	{
		free(str[i]);
	}

	HashDestroy(ht);
}
static void test1()
{
	hash_t *ht = NULL;
	size_t size = 10;

	char *s1 = NULL;
	char *s2 = NULL;
	char *s3 = NULL;

	ht = HashCreate(hash_func_words, same_word, size);

	if (!(HashSize(ht) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (0 == HashIsEmpty(ht))
	{
		printf("fail in %d\n", __LINE__);
	}

	s1 = (char *)malloc(20);
	if (!s1)
	{
		return;
	}
	strcpy(s1, "Hello world");
	HashInsert(ht, s1);

	s2 = (char *)malloc(20);
	if (!s2)
	{
		return;
	}
	strcpy(s2, "Hello world");
	HashInsert(ht, s2);

	s3 = (char *)malloc(20);
	if (!s3)
	{
		return;
	}
	strcpy(s3, "wow");
	HashInsert(ht, s3);

	if (!(3 == HashSize(ht)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HashIsEmpty(ht))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HashFind(ht, "DUMBELDORE"))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!HashFind(ht, "wow"))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(strcmp(HashFind(ht, "wow"), "wow") == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!HashFind(ht, "Hello world"))
	{
		printf("fail in %d\n", __LINE__);
	}

	HashRemove(ht, s1);

	if (!(2 == HashSize(ht)))
	{
		printf("fail in %d\n", __LINE__);
	}

	HashRemove(ht, HashFind(ht, "wow"));

	if (!(1 == HashSize(ht)))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (HashIsEmpty(ht))
	{
		printf("fail in %d\n", __LINE__);
	}

	free(s1);
	free(s2);
	free(s3);
	HashDestroy(ht);
}

static size_t hash_func_words(const void *new_elem)
{
	size_t res = 0;
	char *str = (char *)new_elem;
	while (*str)
	{
		res += (size_t)*str;
		++str;
	}
	return res;
}

static int same_word(void *data, void *param)
{
	return !strcmp((char *)data, (char *)param);
}
