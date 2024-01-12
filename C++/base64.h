#ifndef __BASE64_H__
#define __BASE64_H__

#include <iostream>
#include <vector>

class Base64{

public:
    
    static std::string b64encode(const void *inbuf, size_t inlen){
        size_t pos = 0;
        std::string outbuf;
        const unsigned char *buf = nullptr;
        if(inbuf != NULL && inlen > 0){
            buf = static_cast<const unsigned char *>(inbuf);
            while(pos < inlen){
                outbuf.push_back(TABLE[(buf[pos] >> 2)]);
                outbuf.push_back(TABLE[(((buf[pos] & 3) << 4) | (buf[pos + 1] >> 4))]);
                if((inlen - pos) > 1)
                    outbuf.push_back(TABLE[(((buf[pos + 1] & 15) << 2) | (buf[pos + 2] >> 6))]);
                else
                    outbuf.push_back('=');
                if((inlen - pos) > 2)
                    outbuf.push_back(TABLE[(buf[pos + 2] & 63)]);
                else
                    outbuf.push_back('=');
                pos += 3;
            }
        }
        return outbuf;
    }

    static void *b64decode(const std::string &inbuf){
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
        return static_cast<void *>(const_cast<char *>(outbuf.c_str()));
    }
    
    static void *b64decode(const char *inbuf, const size_t inlen){
        size_t pos = 0;
        std::string outbuf;
        while(pos < inlen){
            outbuf.push_back((TABLE.find(inbuf[pos]) << 2) | (TABLE.find(inbuf[pos + 1]) >> 4));
            if(inbuf[pos + 2] != '=')
                outbuf.push_back(((TABLE.find(inbuf[pos + 1]) & 15) << 4) | (TABLE.find(inbuf[pos + 2]) >> 2));
            if(inbuf[pos + 3] != '=')
                outbuf.push_back(((TABLE.find(inbuf[pos + 2]) & 3) << 6) | TABLE.find(inbuf[pos + 3]));
            pos += 4;
        }
        return static_cast<void *>(const_cast<char *>(outbuf.c_str()));
    }

private:
    static const std::string TABLE;
};

const std::string Base64::TABLE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";



#endif
