#ifndef __PROTECTION_H__
#define __PROTECTION_H__

#include <iostream>
#include <vector>
#include <windows.h>
#include <dpapi.h>

class DPAPI{

public:

    static std::vector<unsigned char> encrypt(std::string plain_text, std::vector<unsigned char> entropy = std::vector<unsigned char>()){
        DATA_BLOB out;
        DATA_BLOB plain;
        DATA_BLOB entrop;
        std::vector<unsigned char> cipher;

        plain.pbData = reinterpret_cast<unsigned char*>(plain_text.data());
        plain.cbData = plain_text.size();
        entrop.pbData = entropy.data();
        entrop.cbData = entropy.size();

        if(CryptProtectData(&plain, nullptr, &entrop, nullptr, nullptr, CRYPTPROTECT_LOCAL_MACHINE, &out) == true){
            for(DWORD index = 0; index < out.cbData; index++)
                cipher.push_back(out.pbData[index]);
            LocalFree(out.pbData);
        }
        return cipher;
    }

    static std::vector<unsigned char> decrypt(std::vector<unsigned char> cipher_text, std::vector<unsigned char> entropy = std::vector<unsigned char>()){
        DATA_BLOB out;
        DATA_BLOB encrypt;
        DATA_BLOB entrop;
        std::vector<unsigned char> plain;

        encrypt.pbData = cipher_text.data();
        encrypt.cbData = cipher_text.size();
        entrop.pbData = entropy.data();
        entrop.cbData = entropy.size();

        if(CryptUnprotectData(&encrypt, nullptr, &entrop, nullptr, nullptr, CRYPTPROTECT_LOCAL_MACHINE, &out) == true){
            for(DWORD index = 0; index < out.cbData; index++)
                plain.push_back(out.pbData[index]);
            LocalFree(out.pbData);
        }
        return plain;
    }
};


#endif
