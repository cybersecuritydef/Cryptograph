#include <stdio.h>
#include <stdlib.h>

void xor(const char *txt, const char *key, const size_t key_len, char *txt_xor, const size_t len){
    int index = 0;
    if(txt != NULL && key != NULL && txt_xor != NULL && len >= strlen(txt)){
        for(index = 0; index < len; index++)
            txt_xor[index] = txt[index] ^ key[index % key_len];
    }
}
