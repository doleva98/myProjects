#include <stdio.h>
#include "fsm.h"
	
int IsZeroAtBeginAndEnd(const unsigned char c)
{
	size_t i = 0;
	int is_good = 0;
	if (c & 1)
	{
		return 0;
	}
	for (i = 1; i < 8; ++i)
	{
		switch ((c >> i) & 1)
		{
		case 0:
			is_good = 1;
			break;
		case 1:
			is_good = 0;
			break;
		}
	}
	return is_good;
}