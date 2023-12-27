#ifndef __BASE64_H__
#define __BASE64_H__

#include <iostream>
#include <vector>

class Base64{

public:

    static std::string encode(std::string plainText){
        size_t len = plainText.size();
        size_t pos = 0;
        std::string encoded;
        while(pos < len){
            encoded.push_back(TABLE[(plainText[pos] >> 2)]);
            encoded.push_back(TABLE[(((plainText[pos] & 3) << 4) | (plainText[pos + 1] >> 4))]);
            if((len - pos) > 1)
                encoded.push_back(TABLE[(((plainText[pos + 1] & 15) << 2) | (plainText[pos + 2] >> 6))]);
            else
                encoded.push_back('=');
            if((len - pos) > 2)
                encoded.push_back(TABLE[(plainText[pos + 2] & 63)]);
            else
                encoded.push_back('=');
            pos += 3;
        }
        return encoded;
    }

    static std::string decode(std::string encodeText){
        size_t len = encodeText.size();
        size_t pos = 0;
        std::string decoded;
        while(pos < len){
            decoded.push_back((TABLE.find(encodeText[pos]) << 2) | (TABLE.find(encodeText[pos + 1]) >> 4));
            if(encodeText[pos + 2] != '=')
                decoded.push_back(((TABLE.find(encodeText[pos + 1]) & 15) << 4) | (TABLE.find(encodeText[pos + 2]) >> 2));
            if(encodeText[pos + 3] != '=')
                decoded.push_back(((TABLE.find(encodeText[pos + 2]) & 3) << 6) | TABLE.find(encodeText[pos + 3]));
            pos += 4;
        }
        return decoded;
    }

private:
    static const std::string TABLE;
};

const std::string Base64::TABLE = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";



#endif
