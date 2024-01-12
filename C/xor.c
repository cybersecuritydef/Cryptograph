#include <stdio.h>
#include <stdlib.h>

void xor(const unsigned char *inbuf, const size_t inlen, const char *key, const int keylen, unsigned char *outbuf, const int outlen){
    int index = 0;
    if(inbuf != NULL && key != NULL && outbuf != NULL && inlen > 0 && outlen > 0){
        for(index = 0; index < inlen; index++){
            outbuf[index] = inbuf[index] ^ key[index % keylen];
        }   
    }
}
