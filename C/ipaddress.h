#ifndef __IPADDRESS_H__
#define __IPADDRESS_H__

#define VALID_PREFIX(x) ((x >= 0) && (x <= 32))

typedef struct _list_address{
    char address[16];
    struct _list_address *next;
}list_address;

unsigned long to_ip_addr_dec(const char *ipaddr);

int to_ip_addr_string(const unsigned long addr, char *ip_str, const size_t len);

int prefix_to_netmask(const size_t prefix, char *netmask, const size_t len);

int netmask_to_prefix(const char *netmask);

size_t count_addresses(const char *netmask);

size_t count_hosts(const char *netmask);

int wild_mask(const char *netmask, char *wild, const size_t len);

int network_address(const char *addr, const char *netmask, char *net_addr, const size_t len);

int addr_broadcast(const char *ipaddr, const char *netmask, char *broadcast, const size_t len);

int min_addr_host(const char *addr, const char *netmask, char *min_addr, const size_t len);

int max_addr_host(const char *addr, const char *netmask, char *max_addr, const size_t len);

list_address *hosts(const char *addr, const char *netmask);

list_address *addresses(const char *addr, const char *netmask);

void list_address_free(list_address **ls);

#endif // __IPADDRESS_H__
