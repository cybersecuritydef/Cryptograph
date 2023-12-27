#include "ipaddress.h"

IPAddress::IPAddress(){

}

IPAddress::IPAddress(const IPAddress &ipaddr){
    address = ipaddr.address;
    netmask = ipaddr.netmask;
    network = ipaddr.network;
    broadcast = ipaddr.broadcast;
    minHost = ipaddr.minHost;
    maxHost = ipaddr.maxHost;
    numHosts = ipaddr.numHosts;
    numAddress = ipaddr.numAddress;
    maskPrefix = ipaddr.maskPrefix;
    intAddress = ipaddr.intAddress;
}

IPAddress &IPAddress::operator = (const IPAddress &ipaddr){
    if(this != &ipaddr){
        address = ipaddr.address;
        netmask = ipaddr.netmask;
        network = ipaddr.network;
        broadcast = ipaddr.broadcast;
        minHost = ipaddr.minHost;
        maxHost = ipaddr.maxHost;
        numHosts = ipaddr.numHosts;
        numAddress = ipaddr.numAddress;
        maskPrefix = ipaddr.maskPrefix;
        intAddress = ipaddr.intAddress;
    }
    return *this;
}

IPAddress::IPAddress(unsigned long ipaddr){
    setAddress(ipaddr);
}

IPAddress::IPAddress(const std::string &ipaddrPrefix){
    setAddress(ipaddrPrefix);
}

IPAddress::IPAddress(const std::string &ipaddr, const std::string &mask){
    setAddress(ipaddr, mask);
}

IPAddress::~IPAddress(){

}

void IPAddress::setAddress(unsigned long ipaddr){
    intAddress = ipaddr;
}

void IPAddress::setAddress(const std::string &ipaddrPrefix){
    std::vector<std::string> addrPrefix = split(ipaddrPrefix, "/");
    if(addrPrefix.size() == 1 && isValidAddress(addrPrefix[0]) == true){
        address = addrPrefix[0];
        intAddress = toIPAddress();
        netmask = NETMASK[32];
        maskPrefix = 32;
    }
    else if(isValidAddress(addrPrefix[0]) == true && VALID_PREFIX(std::stol(addrPrefix[1]))){
        address = addrPrefix[0];
        intAddress = toIPAddress();
        netmask = NETMASK[std::stol(addrPrefix[1])];
        maskPrefix = std::stol(addrPrefix[1]);
    }
}

void IPAddress::setAddress(const std::string &ipaddr, const std::string &mask){
    if(isValidAddress(ipaddr) == true && isValidAddress(mask) == true){
        address = ipaddr;
        intAddress = toIPAddress();
        netmask = mask;
        maskPrefix = toPrefix(mask);
    }
}

std::vector<std::string> IPAddress::hosts(){
    std::string addr = minAddressHost();
    size_t num = countHosts();
    std::vector<std::string> listHosts;
    for(size_t index = 0; index < num; index++)
        listHosts.push_back(toString(toIPAddress(addr) + index));
    return listHosts;
}

std::vector<std::string> IPAddress::addresses(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        std::string net = networkAddress();
        size_t num = countAddress();
        std::vector<std::string> listAddresses;
        for(size_t index = 0; index < num; index++)
            listAddresses.push_back(toString(toIPAddress(net) + index));
        return listAddresses;
    }
    return std::vector<std::string>();
}


std::vector<std::string> IPAddress::subnets(size_t bit){
    std::vector<std::string> listSubnet;
    size_t bits = 32;
    size_t prefix = 0;
    size_t numSubnet = 0;
    std::stringstream buf;
    prefix = toPrefix(netmask);
    prefix += bit;
    if(VALID_PREFIX(prefix)){
        bits -= prefix;
        numSubnet = pow(2, bit);
        for(size_t index = 0; index < numSubnet; index++){
            buf << (toString((toIPAddress(address) & toIPAddress(netmask)) | (index << bits))) << '/' << prefix;
            listSubnet.push_back(buf.str());
            buf.str("");
        }
        return listSubnet;
    }
    return std::vector<std::string>();
}

std::string IPAddress::wildMask(){
    if(isValidAddress(netmask) == true){
        return toString(~toIPAddress(netmask));
    }
    return std::string();
}

std::string IPAddress::wildMask(const std::string &mask){
    if(isValidAddress(mask) == true){
        return toString(~toIPAddress(mask));
    }
    return std::string();
}

int IPAddress::toPrefix(const std::string &mask){
    size_t index = 0;
    if(isValidAddress(mask) == true){
        for(index = 0; index < NETMASK.size(); index++)
            if(NETMASK[index] == mask)
                return index;
    }
    return EOF;
}

int IPAddress::toPrefix(){
    size_t index = 0;
    if(isValidAddress(netmask) == true){
        for(index = 0; index < NETMASK.size(); index++)
            if(NETMASK[index] == netmask)
                return index;
    }
    return EOF;
}

bool IPAddress::isValidAddress() const{
    std::regex ipMask("(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");
    return std::regex_match(address, ipMask);
}

bool IPAddress::isValidAddress(const std::string &addr) const{
    std::regex ipMask("(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)");
    return std::regex_match(addr, ipMask);
}

size_t IPAddress::countHosts(){
    if( isValidAddress(netmask) == true){
        if(toPrefix(netmask) == 31){
            numHosts = pow(2, (32 - toPrefix(netmask)));
            return numHosts;
        }
        else if(toPrefix(netmask) < 31){
            numHosts = pow(2, (32 - toPrefix(netmask))) - 2;
            return numHosts;
        }
    }
    return 0;
}

size_t IPAddress::countAddress(){
    if(isValidAddress(netmask) == true){
        numAddress = pow(2, (32 - toPrefix(netmask)));
        return numAddress;
    }
    return 0;
}

std::string IPAddress::ipaddress(){
    if(isValidAddress(address) == true)
        return address;
    return std::string();
}

std::string IPAddress::networkAddress(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        network = toString((toIPAddress(address) & toIPAddress(netmask)));
        return network;
    }
    return std::string();
}

std::string IPAddress::networkBroadcast(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        broadcast = toString((toIPAddress(address) & toIPAddress(netmask)) | (~toIPAddress(netmask)));
        return broadcast;
    }
    return std::string();
}

std::string IPAddress::minAddressHost(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        if(netmask == "255.255.255.255")
            minHost = address;
        else if(netmask == "255.255.255.254")
            minHost = toString((toIPAddress(address) & toIPAddress(netmask)));
        else
            minHost = toString((toIPAddress(address) & toIPAddress(netmask)) + 1);
        return minHost;
    }
    return std::string();
}

std::string IPAddress::maxAddressHost(){
    if(isValidAddress(address) == true && isValidAddress(netmask) == true){
        if(netmask == "255.255.255.255")
            maxHost = address;
        else if(netmask == "255.255.255.254")
            maxHost = toString((toIPAddress(address) & toIPAddress(netmask)) + 1);
        else
            maxHost = toString((toIPAddress(address) & toIPAddress(netmask)) | (~toIPAddress(netmask) - 1));
        return maxHost;
    }
    return std::string();
}

unsigned long IPAddress::toIPAddress(std::string ip){
    std::vector<std::string> items;
    if(isValidAddress(ip) == true){
        items = split(ip, ".");
        return (std::stol(items[0]) << 24 | std::stol(items[1]) << 16 | std::stoi(items[2]) << 8 | std::stol(items[3]));
    }
    return 0;
}

unsigned long IPAddress::toIPAddress(){
    std::vector<std::string> items;
    if(isValidAddress(address) == true){
        items = split(address, ".");
        intAddress = (std::stol(items[0]) << 24 | std::stol(items[1]) << 16 | std::stoi(items[2]) << 8 | std::stol(items[3]));
        return intAddress;
    }
    return 0;
}

std::string IPAddress::toString(unsigned long ip){
    std::string ipaddr;
    std::stringstream s;
    s << ((ip >> 24) & 0xff) << '.';
    s << ((ip >> 16) & 0xff) << '.';
    s << ((ip >> 8) & 0xff) << '.';
    s << ((ip & 0xff));
    s >> ipaddr;
    return ipaddr;
}

std::string IPAddress::toString(){
    std::string ipaddr;
    std::stringstream s;
    s << ((intAddress >> 24) & 0xff) << '.';
    s << ((intAddress >> 16) & 0xff) << '.';
    s << ((intAddress >> 8) & 0xff) << '.';
    s << ((intAddress & 0xff));
    s >> ipaddr;
    return ipaddr;
}

bool IPAddress::operator == (const IPAddress &ipaddr){
    if(address == ipaddr.address && netmask == ipaddr.netmask && network == ipaddr.network && broadcast == ipaddr.broadcast && minHost == ipaddr.minHost && maxHost == ipaddr.maxHost && numHosts == ipaddr.numHosts && numAddress == ipaddr.numAddress && maskPrefix == ipaddr.maskPrefix && intAddress == ipaddr.intAddress)
        return true;
    return false;
}

bool IPAddress::operator != (const IPAddress &ipaddr){
    return !(*this == ipaddr);
}

std::vector<std::string> IPAddress::split(const std::string &str, const char *delim){
    std::vector<std::string> lists;
    std::string tmp = str;
    char *s = nullptr;
    if(tmp.size() > 0 && delim != nullptr){
        s = strtok(const_cast<char*>(tmp.c_str()), delim);
        while(s != nullptr){
            lists.push_back(s);
            s = strtok(nullptr, delim);
        }
        return lists;
    }
    return std::vector<std::string>();
}
