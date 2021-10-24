#include "/home/dolev/git/dolev-arev/include/utils.h"
#include <limits.h> 

static int Bursa(int *a, int *low, int *high, int len);

int main() {

    int a [] = {6,12,60,30,1,4,9,2};
    int low = 0;
    int high = 0;
    printf("%d\n", Bursa(a, &low, &high, sizeof(a)/sizeof(*a)));
    printf("%d\n", low);
    printf("%d\n", high); 

   return 0;
}

static int Bursa(int *a, int *low, int *high, int len)
{
	int low_temp = 0;
	int max_diff = 0;
	int i = 0;
	*high = 0;
	*low = 0;
	
	
	if(len <= 1)
	{
		return max_diff;
	}
	

	for(; i < len; ++i)
	{
		if(a[i] <= a[low_temp])
		{
			low_temp = i;
		} 
		else if(a[i] - a[low_temp] > max_diff)
		{
			max_diff = a[i] - a[low_temp];
			*low = low_temp;
			*high = i;
		}
		
	}
	return max_diff;
}








