#include <stdio.h>
#include "stack.h"
#include <string.h>

int main()
{

    Stack_t *stack = NULL;
    char *s = NULL;
    int b;
    int f;
    char *last = NULL;

    s = (char *)calloc(100, sizeof(char));
    if (!s)
    {
        fprintf(stderr, "out of memory");
        exit(1);
    }

    strcpy(s, "Hello world");
    b = 5;
    f = 3;

    stack = StackCreate(5);

    if (!(1 == StackIsEmpty(stack)))
    {
        printf("fail in %d\n", __LINE__);
    }

    StackPush(stack, s);

    if (!(strcmp("Hello world", (char *)StackPeek(stack)) == 0))
    {
        printf("fail in %d\n", __LINE__);
    }

    StackPush(stack, &b);

    if (!(5 == *(int *)StackPeek(stack)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(0 == StackIsEmpty(stack)))
    {
        printf("fail in %d\n", __LINE__);
    }

    StackPush(stack, &f);
    if (!(3 == *(int *)StackPeek(stack)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(3 == StackSize(stack)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(5 == StackCapacity(stack)))
    {
        printf("fail in %d\n", __LINE__);
    }

    StackPop(stack);

    if (!(2 == StackSize(stack)))
    {
        printf("fail in %d\n", __LINE__);
    }

    if (!(5 == *(int *)StackPeek(stack)))
    {
        printf("fail in %d\n", __LINE__);
    }

    last = (char *)calloc(100, sizeof(char));
    if (!last)
    {
        fprintf(stderr, "out of memory");
        exit(1);
    }

    strcpy(last, "BYe byeeee Dumbeldore");
    StackPush(stack, last);

    if (!(strcmp("BYe byeeee Dumbeldore", (char *)StackPeek(stack)) == 0))
    {
        printf("fail in %d\n", __LINE__);
    }

    free(last);
    free(s);
    StackDestroy(stack);

    return 0;
}
