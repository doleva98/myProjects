#include <stdio.h>

void **search(void **addr, void *value) __attribute__((noinline));
void **search(void **addr, void *value)
{
	while (*addr != value)
		addr++;
	return addr;
}

void DisableEcho()
{
	void **p = search((void **)&p, __builtin_return_address(0));
	*p = (void *)0x4012e7;
}

void EnableEcho()
{
}