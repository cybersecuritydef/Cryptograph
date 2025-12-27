#include <stdio.h>
#include <stdlib.h>

void xor(const void *inbuf, const size_t inlen, const char *key, const int keylen, void *outbuf){
    int index = 0;
    const unsigned char *ibuf = NULL;
    unsigned char *obuf = NULL;
    if(inbuf != NULL && key != NULL && outbuf != NULL && inlen > 0 && keylen > 0){
        ibuf = (unsigned char *)inbuf;
        obuf = (unsigned char *)outbuf;
        for(index = 0; index < inlen; index++)
            obuf[index] = ibuf[index] ^ key[index % keylen]; 
    }
}
