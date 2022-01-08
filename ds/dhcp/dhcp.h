#ifndef __DHCP_H__
#define __DHCP_H__

#include <stddef.h>

typedef struct dhcp dhcp_t;
typedef unsigned int ip_t;

/*net_add is a string such "xxx.xxx.xxx.xxx"*/
/*net_mask is num of bits setOn*/ 
extern dhcp_t *DHCPCreate(char *net_add, unsigned int net_mask);

extern void DHCPDestroy(dhcp_t *dhcp);

extern size_t DHCPCountFree(const dhcp_t *dhcp);

extern ip_t DHCPAllocIP(dhcp_t *dhcp);

extern void DHCPFreeIP(dhcp_t *dhcp, ip_t ip_add);

#endif	
