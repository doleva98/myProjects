#include <stdio.h>
#include <stdlib.h>
#include "calculator.h"
#include <assert.h>
int main()
{
	char str[100] = "20.30300 + 48.694 - 17 * 25.34 + 4 / 2";
	char str2[50] = "2+3 * 16.5 +22 * (15.5*16.2) +1";
	char str3[10] = "-7+14";
	assert(!(int)(Calculate(str) + 359.783000));

	assert(!(int)((Calculate(str2) - 5576.70)));
	assert(!(int)(Calculate(str3) - 7));

	/*testing unary and binary states*/
	assert(Calculate("1") == 1);
	assert(Calculate("+1") == 1);
	assert(Calculate("-1") == -1);
	assert(Calculate("-1 + 1") == 0);
	assert(Calculate("-1 - 1") == -2);
	assert(Calculate("-1 - -1") == 0);
	assert(Calculate("1 - -1") == 2);
	assert(Calculate("+1 - 1") == 0);
	assert(Calculate("-1 * (-1 + 2)") == -1);
	assert(Calculate("-1 * (-1 - 2)") == 3);

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

	if (!(6.5 == Calculate("(6.5)")))
	{
		printf("fail in %d\n", __LINE__);
	}
	if (!(1.5 == Calculate("(-6.5 + 9)-1")))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(5 == Calculate("2--3")))
	{
		printf("fail in %d\n", __LINE__);
	}
	return 0;
}
