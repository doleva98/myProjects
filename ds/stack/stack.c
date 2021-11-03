#include <stdio.h>
#include "stack.h"

struct Stack
{
	size_t capacity;
	size_t top;
	void **a;
};


/*Return a new stack*/
extern Stack_t *StackCreate(size_t capacity)
{
	Stack_t *stack = NULL;
	
	stack = (Stack_t*)calloc(1, sizeof(Stack_t));
	if(!stack)
	{
		return NULL;
	}
	stack->capacity = capacity;
	stack->top = 0;
	stack->a = (void**)calloc(capacity, sizeof(void**));
	return stack;
}

/*Delete the stack */
extern void StackDestroy(Stack_t *stack)
{	
	free(stack->a);
	stack->a = NULL;
	free(stack);
	stack = NULL;
}

/*Add a new element to the top of the stack */
extern void StackPush(Stack_t *stack, void* new_element)
{	
	stack->a[stack->top] = new_element;
	++stack->top;
}

/*Remove the last element */
extern void StackPop(Stack_t *stack)
{
	--stack->top;
}

/*Return the value of the last element */
extern void* StackPeek(Stack_t *stack)
{
	return stack->a[stack->top - 1];
}

/*Check if the array is empty, Return 0 or 1*/
extern int StackIsEmpty(Stack_t *stack)
{
	return stack->top == 0;
}

/*Return how many elements are used*/
extern size_t StackSize(Stack_t *stack)
{
	return stack->top;
}

/*Check the capacity, Return the capacity*/
extern size_t StackCapacity(Stack_t *stack)
{
	return stack->capacity;
}


