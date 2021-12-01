#include <stdio.h>
#include <stdlib.h>

int A = 42;
const int B = 411;
static int C = 90;
static const int D = 21;

static void staticFoo(int i);
extern void externFoo(int i);

int main(int argc, char **argv, char **envp)
{
	char *str = NULL;
	int a = 4;
	const int b = 24;
	static int c = 9;
	static const int d = 1;

	char *str2 = "Dumbeldore";

	staticFoo(0);
	externFoo(3);

	str = (char *)malloc(100);
	if (!str)
	{
		fprintf(stderr, "OUT OF MEMORY");
	}

	return 0;
}

static void staticFoo(int i)
{
	printf("i am static and i have %d", i);
}

void externFoo(int i)
{
	printf("i am extern and i have %d", i);
}