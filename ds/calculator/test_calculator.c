#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
int main()
{
	if (!(5 == Calculate("1+4")))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(110 == Calculate("100 + 60   - 50")))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(20 == Calculate("10*6/3")))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(5 == Calculate("10/6*3")))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(-90 == Calculate("(  10   -5.00*   (3    +  2  )    *4)   ")))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(6.5 == Calculate("5.5+(0.5*2)")))
	{
		printf("fail in %d\n", __LINE__);
	}
	return 0;
}
