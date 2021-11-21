#include "../../ds/stack/stack.h"

char *Parentheses(char *str, int len)
{

	Stack_t *stack = StackCreate(len);
	char c;
	while(*str)
	{

		if(*str == '{' || *str == '(' || *str == '[')
		{
			c = *str;
			StackPush(stack, &c);
			printf("%c", *(char*)StackPeek(stack));	
			printf("%c", c);	
		}
		
		else {
		if(*str == '}' || *str == ')' || *str == ']')
		{

			if(StackIsEmpty(stack))
			{
				return "Not Balanced";
			}

			switch (*str)
			{
			case '}':
				if(*(char*)StackPeek(stack) == '{'){
					StackPop(stack);
				}		
				break;
			case ')':
				if(*(char*)StackPeek(stack) == '(')
				{
					StackPop(stack);
				}
				break;
			case ']':
				if(*(char*)StackPeek(stack) == '['){
					StackPop(stack);

				}
				break;
			}
		}
		}
		++str;

	}
	if(!StackIsEmpty(stack))
	{
		return "Not Balanced";
	}
	return "Balanced";
}

