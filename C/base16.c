#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char TABLE[] = "0123456789ABCDEF";

void b16encode(const char *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    if(inbuf != NULL && outbuf != NULL && outlen > inlen){
        while(pos < inlen){
            outbuf[index++] = TABLE[inbuf[pos] >> 4];
            outbuf[index++] = TABLE[inbuf[pos++] & 15];
        }
        outbuf[index] = '\0';
    }
}

void b16decode(const char *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    if(inbuf != NULL && outbuf != NULL && outlen > inlen){
        while(pos < inlen){
            outbuf[index++] = ((int)(strchr(TABLE, inbuf[pos]) - TABLE) << 4) | (int)((strchr(TABLE, inbuf[pos + 1])) - TABLE);
            pos += 2;
        }
        outbuf[index] = '\0';
    }
}
