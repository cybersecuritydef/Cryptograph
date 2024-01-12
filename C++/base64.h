#ifndef __BASE64_H__
#define __BASE64_H__

#include <iostream>
#include <vector>

class Base64{

public:

    static std::string encode(std::string inbuf){
        size_t len = inbuf.size();
        size_t pos = 0;
        std::string outbuf;
        while(pos < len){
            outbuf.push_back(TABLE[(inbuf[pos] >> 2)]);
            outbuf.push_back(TABLE[(((inbuf[pos] & 3) << 4) | (inbuf[pos + 1] >> 4))]);
            if((len - pos) > 1)
                outbuf.push_back(TABLE[(((inbuf[pos + 1] & 15) << 2) | (inbuf[pos + 2] >> 6))]);
            else
                outbuf.push_back('=');
            if((len - pos) > 2)
                outbuf.push_back(TABLE[(inbuf[pos + 2] & 63)]);
            else
                outbuf.push_back('=');
            pos += 3;
        }
        return outbuf;
    }

    static std::string decode(std::string inbuf){
        size_t len = inbuf.size();
        size_t pos = 0;
        std::string outbuf;
        while(pos < len){
            outbuf.push_back((TABLE.find(inbuf[pos]) << 2) | (TABLE.find(inbuf[pos + 1]) >> 4));
            if(inbuf[pos + 2] != '=')
                outbuf.push_back(((TABLE.find(inbuf[pos + 1]) & 15) << 4) | (TABLE.find(inbuf[pos + 2]) >> 2));
            if(inbuf[pos + 3] != '=')
                outbuf.push_back(((TABLE.find(inbuf[pos + 2]) & 3) << 6) | TABLE.find(inbuf[pos + 3]));
            pos += 4;
        }
        return outbuf;
    }

private:
    static const std::string TABLE;
};

const std::string Base64::TABLE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";



#endif
