#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char TABLE[] = "0123456789abcdef";

void urlencode(const char *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    if(inbuf != NULL && outbuf != NULL && outlen > inlen){
        while(pos < inlen){
            outbuf[index++] = '%';
            outbuf[index++] = TABLE[tolower(inbuf[pos]) >> 4];
            outbuf[index++] = TABLE[tolower(inbuf[pos++]) & 15];
        }
        outbuf[index] = '\0';
    }
}

void urldecode(const char *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    if(inbuf != NULL && outbuf != NULL && outlen > inlen){
        while(pos < inlen){
            outbuf[index++] = ((int)(strchr(TABLE, tolower(inbuf[pos + 1])) - TABLE) << 4) | (int)(strchr(TABLE, tolower(inbuf[pos + 2])) - TABLE);
            pos += 3;
        }
        outbuf[index] = '\0';
    }
}
