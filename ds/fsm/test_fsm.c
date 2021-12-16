#include <stdio.h>
#include "fsm.h"
int main()
{
	if (!(IsZeroAtBeginAndEnd(0xFF) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(IsZeroAtBeginAndEnd(0xF8) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(IsZeroAtBeginAndEnd(0x1) == 0))
	{
		printf("fail in %d\n", __LINE__);
	}

	if (!(IsZeroAtBeginAndEnd(0x43) == 1))
	{
		printf("fail in %d\n", __LINE__);
	}

	return 0;
}
