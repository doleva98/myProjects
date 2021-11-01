#include "/home/dolev/git/dolev-arev/include/utils.h"

void findDup(int *a, int len)
{	
	int i = 0;
	int j;
	int *b = (int*)calloc(sizeof(int), len);
	
	for(; i < len; ++i)
	{
		for(j = i + 1; j < len; ++j)
		{
			if(a[i] == a[j])
			{
				if(!b[i])
				{
					printf("%d\n", a[i]);
				}
				++b[i];
				++b[j];
			}
		}
	}
	FREE(b);
	
}

int main() {

    int a [] = {4,2,3,4,4,4,2};
	findDup(a, 7); 
   return 0;
}
