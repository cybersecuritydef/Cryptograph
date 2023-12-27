#ifndef __BASE16_H__
#define __BASE16_H__

#include <iostream>

class Base16{

public:

    static std::string encode(std::string plainText){
        size_t len = plainText.size();
        size_t pos = 0;
        std::string encoded;
        while(pos < len){
            encoded.push_back(TABLE[plainText[pos] >> 4]);
            encoded.push_back(TABLE[plainText[pos] & 15]);
            pos++;
        }
        return encoded;
    }

    static std::string decode(std::string encodeText){
        size_t len = encodeText.size();
        size_t pos = 0;
        std::string decoded;
        while(pos < len){
            decoded.push_back((TABLE.find(encodeText[pos]) << 4) | TABLE.find(encodeText[pos + 1]));
            pos += 2;
        }
        return decoded;
    }

private:
    static const std::string TABLE;
};

const std::string Base16::TABLE = "0123456789ABCDEF";



#endif
