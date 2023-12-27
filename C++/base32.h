#ifndef __BASE32_H__
#define __BASE32_H__

#include <iostream>
#include <vector>

class Base32{

public:

    static std::string encode(std::string plainText){
        size_t len = plainText.size();
        size_t pos = 0;
        std::string encoded;
        while(pos < len){
            encoded.push_back(TABLE[(plainText[pos] >> 3) & 31]);
            encoded.push_back(TABLE[((plainText[pos] << 2) | (plainText[pos + 1] >> 6)) & 31]);
            if((len - pos) > 1)
                encoded.push_back(TABLE[((plainText[pos + 1] >> 1) & 31)]);
            else
                encoded.push_back('=');

            if((len - pos) > 1)
                encoded.push_back(TABLE[((plainText[pos + 1] << 4) | (plainText[pos + 2] >> 4)) & 31]);
            else
                encoded.push_back('=');

            if((len - pos) > 2)
                encoded.push_back(TABLE[((plainText[pos + 2] << 1) | (plainText[pos + 3] >> 7)) & 31]);
            else
                encoded.push_back('=');

            if((len - pos) > 3)
                encoded.push_back(TABLE[(plainText[pos + 3] >> 2) & 31]);
            else
                encoded.push_back('=');

            if((len - pos) > 3)
                encoded.push_back(TABLE[((plainText[pos + 3] << 3) | (plainText[pos + 4] >> 5)) & 31]);
            else
                encoded.push_back('=');

            if((len - pos) > 4)
                encoded.push_back(TABLE[(plainText[pos + 4] & 31)]);
            else
                encoded.push_back('=');
            pos += 5;
        }
        return encoded;
    }

    static std::string decode(std::string encodeText){
        size_t len = encodeText.size();
        size_t pos = 0;
        std::string decoded;
        while(pos < len){
            decoded.push_back(((TABLE.find(encodeText[pos]) << 3) | (TABLE.find(encodeText[pos + 1]) >> 2)));
            if(encodeText[pos + 2] != '=')
                decoded.push_back(((TABLE.find(encodeText[pos + 1]) << 6) | (TABLE.find(encodeText[pos + 2]) << 1) | (TABLE.find(encodeText[pos + 3]) >> 4)));
            if(encodeText[pos + 4] != '=')
                decoded.push_back(((TABLE.find(encodeText[pos + 3]) << 4) | (TABLE.find(encodeText[pos + 4]) >> 1)));
            if(encodeText[pos + 5] != '=')
                decoded.push_back(((TABLE.find(encodeText[pos] + 4) << 7) | (TABLE.find(encodeText[pos + 5]) << 2) | (TABLE.find(encodeText[pos + 6]) >> 3)));
            if(encodeText[pos + 7] != '=')
                decoded.push_back(((TABLE.find(encodeText[pos + 6]) << 5) | TABLE.find(encodeText[pos + 7])));
            pos += 8;
        }
        return decoded;
    }

private:
    static const std::string TABLE;
};

const std::string Base32::TABLE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";



#endif
