#include <stdio.h>

#define MAX2(a,b) (((a)>(b))?(a):(b))
#define MAX3(a,b,c) (MAX2((a),(MAX2((b),(c)))))

#define TO_LOWER(a) (((a) > 'A' && (a) < 'Z')?\
((a) - 'A' + 'a') :(a))

typedef struct
{
	int num;
	char c1;
	int *ptr1;
	char c2;
}s;	



int main() {

    int a = 49;
    int b = 10;
    int c = 80;
    char t = 'Q';

    	
    union u
	{
	int num;
	char a[5];
	}u1;	
    	
    printf("%d\n", MAX2(a,b));
    printf("%d\n", MAX3(a,b,c));

	printf("%c\n", TO_LOWER(t));


		printf("%lu", sizeof(u1));
   return 0;
}
