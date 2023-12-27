#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <cmath>


#define VALID_PREFIX(x) ((x >= 0) && (x <= 32))

class IPAddress{

public:
    IPAddress();
    IPAddress(unsigned long ipaddr);
    IPAddress(const IPAddress &ipaddr);
    IPAddress(const std::string &ipaddrPrefix);
    IPAddress(const std::string &ipAddress, const std::string &mask);
    IPAddress &operator = (const IPAddress &ipaddr);

    ~IPAddress();

    void setAddress(unsigned long ipaddr);
    void setAddress(const std::string &ipaddrPrefix);
    void setAddress(const std::string &ipaddr, const std::string &mask);

    size_t countHosts();
    size_t countAddress();

    std::string ipaddress();
    std::string networkAddress();
    std::string networkBroadcast();
    std::string networkMask() const { return netmask; };
    std::string networkMask(size_t prefix) const { return NETMASK[prefix]; };

    std::string minAddressHost();
    std::string maxAddressHost();

    std::vector<std::string> hosts();
    std::vector<std::string> addresses();

    int toPrefix();
    int toPrefix(const std::string &mask);

    std::string wildMask();
    std::string wildMask(const std::string &mask);

    bool isValidAddress() const;
    bool isValidAddress(const std::string &addr) const;

    std::vector<std::string> subnets(size_t bit = 1);

    std::vector<std::string> listAllNetMask() const{ return NETMASK; }

    unsigned long toIPAddress();
    unsigned long toIPAddress(std::string ip);

    std::string toString();
    std::string toString(unsigned long ip);

    bool operator == (const IPAddress &ipaddr);
    bool operator != (const IPAddress &ipaddr);

private:
    std::string network;
    std::string broadcast;
    std::string minHost;
    std::string maxHost;
    std::string address;
    std::string netmask;

    size_t numHosts = 0;
    size_t numAddress = 0;
    size_t maskPrefix = 0;
    unsigned long intAddress = 0;

    std::vector<std::string>split(const std::string &str, const char *delim);

    const std::vector<std::string> NETMASK = {"0.0.0.0",
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

};

#endif
