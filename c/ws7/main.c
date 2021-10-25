#include "g.h"
#include <stdio.h>

int main()
{

	printf("%d", g_s);
	Foo();
	printf("%d", g_s);

	return 0;
}
