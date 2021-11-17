#include "/home/dolev/git/dolev-arev/include/utils.h"

int MaxSubArr(int *arr, int len, int *low, int *high)
{
	
	int maxHere = 0;
	int maxEnd = 0;	
	int i = 0;
	int startCount = 0;
	for(; i < len; ++i)
	{
		
		maxEnd += arr[i]; 	
		if(maxHere < maxEnd)
		{
			maxHere = maxEnd;
			if(startCount == 0)
			{
				*low = i;
				*high = i;
				startCount = 1;
			}
			else
			{
				*high = i;
			}
		}
		
		if(maxEnd < 0)
		{
			maxEnd = 0;
			startCount = 0;
		}
	}
	return maxHere;
	
}

int main() {

    int a;
    int b;
    int s []= {-2, 1, -3, 4, -1, 2, 3, -5, 4};
    int sum = MaxSubArr(s, 8, &a, &b);
    printf("%d %d %d", a,b, sum);

   return 0;
}
