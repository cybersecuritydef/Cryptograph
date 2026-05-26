#include <stdio.h>
#include <stdlib.h>

void xor(const void *inbuf, const size_t inlen, const void *key, const size_t keylen, void *outbuf){
    size_t index = 0;
    const unsigned char *ibuf = NULL;
    const unsigned char *k = NULL;
    unsigned char *obuf = NULL;
    if(inbuf != NULL && key != NULL && outbuf != NULL && inlen > 0 && keylen > 0){
        ibuf = (unsigned char *)inbuf;
        obuf = (unsigned char *)outbuf;
        k = (unsigned char *)key;
        for(index = 0; index < inlen; index++)
            obuf[index] = ibuf[index] ^ k[index % keylen]; 
    }
}
