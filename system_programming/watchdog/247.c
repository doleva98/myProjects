#include <stdio.h>
#include <unistd.h> /* sleep */
#include "watchdog_lib.h"

int main(int argc, char **argv)
{
	if (KeepMeAlive(argc, argv) == 1)
	{
		return 1;
	}
	while (1)
	{
		/* 		printf("hello world\n");
		 */
		sleep(2);
	}
	return 0;
}