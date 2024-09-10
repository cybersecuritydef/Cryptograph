#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ipaddress.h"

static const char *NETMASK[] = {"0.0.0.0",
                                "128.0.0.0",
                                "192.0.0.0",
                                "224.0.0.0",
                                "240.0.0.0",
                                "248.0.0.0",
                                "252.0.0.0",
                                "254.0.0.0",
                                "255.0.0.0",
                                "255.128.0.0",
                                "255.192.0.0",
                                "255.224.0.0",
                                "255.240.0.0",
                                "255.248.0.0",
                                "255.252.0.0",
                                "255.254.0.0",
                                "255.255.0.0",
                                "255.255.128.0",
                                "255.255.192.0",
                                "255.255.224.0",
                                "255.255.240.0",
                                "255.255.248.0",
                                "255.255.252.0",
                                "255.255.254.0",
                                "255.255.255.0",
                                "255.255.255.128",
                                "255.255.255.192",
                                "255.255.255.224",
                                "255.255.255.240",
                                "255.255.255.248",
                                "255.255.255.252",
                                "255.255.255.254",
                                "255.255.255.255"};


unsigned long to_ip_addr_dec(const char *ipaddr){
    int a;
    int b;
    int c;
    int d;
    if(ipaddr != NULL && sscanf(ipaddr,"%d.%d.%d.%d", &a, &b, &c, &d) == 4)
        return (a << 24 | b << 16 | c << 8 | d);
    return 0;
}

int to_ip_addr_string(const unsigned long addr, char *ip_str, const size_t len){
    if(addr > 0 && ip_str != NULL && len > 0){
        snprintf(ip_str, len, "%lu.%lu.%lu.%lu", ((addr >> 24) & 0xff), ((addr >> 16) & 0xff), ((addr >> 8) & 0xff),(addr & 0xff));
        return 0;
    }
    return EOF;
}

int prefix_to_netmask(const size_t prefix, char *netmask, const size_t len){
    if(netmask != NULL && len > 0 && VALID_PREFIX(prefix)){
        snprintf(netmask, len, "%s", NETMASK[prefix]);
        return 0;
    }
    return EOF;
}

int netmask_to_prefix(const char *netmask){
    size_t index = 0;
    if(netmask != NULL){
        for(index = 0; index < sizeof(NETMASK) / sizeof(NETMASK[0]); index++){
            if(strcmp(NETMASK[index], netmask) == 0)
                return index;
        }
    }
    return EOF;
}

size_t count_addresses(const char *netmask){
    if(netmask != NULL){
        return (size_t)pow(2, (32 - netmask_to_prefix(netmask)));
    }
    return 0;
}

int wild_mask(const char *netmask, char *wild, const size_t len){
    if(netmask != NULL && wild != NULL && len > 0){
        if(strcmp(netmask, "255.255.255.255") == 0)
            snprintf(wild, len, "0.0.0.0");
        else
            to_ip_addr_string(~to_ip_addr_dec(netmask), wild, len);
        return 0;
    }
    return EOF;
}

size_t count_hosts(const char *netmask){
    int prefix = 0;
    if(netmask != NULL){
        prefix = netmask_to_prefix(netmask);
        if(prefix == 31)
            return (size_t)pow(2, (32 - prefix));
        else if(prefix < 31)
            return (size_t)(pow(2, (32 - prefix))) - 2;
    }
    return 0;
}

int addr_broadcast(const char *ipaddr, const char *netmask, char *broadcast, const size_t len){
    unsigned long br = 0;
    if(ipaddr != NULL && netmask != NULL && broadcast != NULL && len > 0){
        br = ((to_ip_addr_dec(ipaddr) & to_ip_addr_dec(netmask)) | (~to_ip_addr_dec(netmask)));
        to_ip_addr_string(br, broadcast, len);
        return 0;
    }
    return EOF;
}

int min_addr_host(const char *addr, const char *netmask, char *min_addr, const size_t len){
    if(addr != NULL && netmask != NULL && min_addr != NULL && len > 0){
        if(strcmp(netmask, "255.255.255.255") == 0)
            snprintf(min_addr, len, "%s", addr);
        else if(strcmp(netmask, "255.255.255.254") == 0)
            to_ip_addr_string(to_ip_addr_dec(addr) & to_ip_addr_dec(netmask), min_addr, len);
        else
            to_ip_addr_string((to_ip_addr_dec(addr) & to_ip_addr_dec(netmask)) + 1, min_addr, len);
        return 0;
    }
    return EOF;
}

int max_addr_host(const char *addr, const char *netmask, char *max_addr, const size_t len){
    if(addr != NULL && netmask != NULL && max_addr != NULL && len > 0){
        if(strcmp(netmask, "255.255.255.255") == 0)
            snprintf(max_addr, len, "%s", addr);
        else if(strcmp(netmask, "255.255.255.254") == 0)
            to_ip_addr_string((to_ip_addr_dec(addr) & to_ip_addr_dec(netmask)) + 1, max_addr, len);
        else
            to_ip_addr_string(((to_ip_addr_dec(addr) & to_ip_addr_dec(netmask)) | (~to_ip_addr_dec(netmask))) - 1, max_addr, len);
        return 0;
    }
    return EOF;
}

int network_address(const char *addr, const char *netmask, char *net_addr, const size_t len){
    if(addr != NULL && netmask != NULL && net_addr != NULL && len > 0){
        to_ip_addr_string((to_ip_addr_dec(addr) & to_ip_addr_dec(netmask)), net_addr, len);
        return 0;
    }
    return EOF;
}

static void add_address(list_address **ls, const char *value){
    list_address *tmp = NULL;
    list_address *p = NULL;
    if(ls != NULL && value != NULL){
        if((tmp = (list_address*)malloc(sizeof(list_address))) != NULL){
            snprintf(tmp->address, 16, "%s", value);
            tmp->next = NULL;
            if((*ls) == NULL)
                (*ls) = tmp;
            else{
                p = (*ls);
                while(p->next != NULL){
                    p = p->next;
                }
                p->next = tmp;
            }
        }
    }
}

list_address *hosts(const char *addr, const char *netmask){
    char min_addr[16] = {'\0'};
    char buf_addr[16] = {'\0'};
    size_t count = 0;
    size_t index = 0;
    list_address *ls = NULL;
    if(addr != NULL && netmask != NULL){
        min_addr_host(addr, netmask, min_addr, 16);
        count = count_hosts(netmask);
        for(index = 0; index < count; index++){
            to_ip_addr_string(to_ip_addr_dec(min_addr) + index, buf_addr, 16);
            add_address(&ls, buf_addr);
        }
        return ls;
    }
    return NULL;
}

list_address *addresses(const char *addr, const char *netmask){
    char net_addr[16] = {'\0'};
    char buf_addr[16] = {'\0'};
    size_t count = 0;
    size_t index = 0;
    list_address *ls = NULL;
    if(addr != NULL && netmask != NULL){
        network_address(addr, netmask, net_addr, 16);
        count = count_addresses(netmask);
        for(index = 0; index < count; index++){
            to_ip_addr_string(to_ip_addr_dec(net_addr) + index, buf_addr, 16);
            add_address(&ls, buf_addr);
        }
        return ls;
    }
    return NULL;
}

void list_address_free(list_address **ls){
    list_address *tmp = NULL;
    if(ls != NULL && (*ls) != NULL){
        while((*ls) != NULL){
            tmp = (*ls);
            (*ls) = (*ls)->next;
            free(tmp);
            tmp = NULL;
        }
    }
}
