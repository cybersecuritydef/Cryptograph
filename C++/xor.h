#ifndef __XOR_H__
#define __XOR_H__

#include <iostream>

class XOR{

public:
    static std::string update(std::string text, std::string key){
        std::string data;
        if(text.size() > 0 && key.size() > 0){
            for(size_t index = 0; index < text.size(); index++)
                data.push_back(text[index] ^ key[index % key.size()]);
        }
        return data;
    }
};

#endif
