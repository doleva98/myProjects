#include <stdio.h>
#include "dhcp.h"

static void PrintIP(ip_t ip);
int main()
{
	char net[] = "123.10.0.0";
	size_t i = 0;
	dhcp_t *dhcp = DHCPCreate(net, 28);
	ip_t temp = 0;
	printf("Free IPs: %lu\n", DHCPCountFree(dhcp));
	for (; i < 12; ++i)
	{
		printf("[%lu] ", i);
		if (i == 0)
		{
			temp = DHCPAllocIP(dhcp);
			PrintIP(temp);
		}
		else
		{
			PrintIP(DHCPAllocIP(dhcp));
		}
	}
	temp = DHCPAllocIP(dhcp);
	PrintIP(temp);
	for (i = 0; i < 10; ++i)
	{
		DHCPFreeIP(dhcp, temp + i);
	}
	DHCPDestroy(dhcp);

	return 0;
}

static void PrintIP(ip_t ip)
{
	printf("%u.%u.%u.%u\n", (unsigned char)(ip >> 24), (unsigned char)(ip >> 16), (unsigned char)(ip >> 8), (unsigned char)ip);
}
