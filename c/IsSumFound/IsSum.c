#include <stdio.h>
#include "/home/dolev/git/dolev-arev/include/utils.h"

int IsSumFound(int a [], int sum, int *indexa, int *indexb, int len)
{
	int head = 0;
	int tail = len - 1;

	while(head != tail)
	{
		if(sum == a[head] + a[tail])
		{
			*indexa = head;
			*indexb = tail;
			return 1;
		} 
		else if (sum < a[head] + a[tail])
		{
			--tail;
		}    
		else
		{
			++head;
		}
	}
	return 0;
}

int main() {
	
	int a [] = {1,2,3,4,5};
	int b = -1;
	int c = -1;
	int len = (int) sizeof(a)/sizeof(*a);
	ASSERT(1 == IsSumFound(a, 9, &b, &c, len));
	ASSERT(3 == b);
	ASSERT(4 == c);
   return 0;
}
