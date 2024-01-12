#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char TABLE[] = "0123456789ABCDEF";

void b16encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    const unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)inbuf;
        while(pos < inlen && index < outlen){
            outbuf[index++] = TABLE[buf[pos] >> 4];
            outbuf[index++] = TABLE[buf[pos++] & 15];
        }
        outbuf[index] = '\0';
    }
}

void b16decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL && outlen > inlen){
        buf = (unsigned char *)outbuf;
        while(pos < inlen){
            buf[index++] = ((int)(strchr(TABLE, inbuf[pos]) - TABLE) << 4) | (int)((strchr(TABLE, inbuf[pos + 1])) - TABLE);
            pos += 2;
        }
        buf[index] = '\0';
    }
}
