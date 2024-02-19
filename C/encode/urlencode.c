#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static const char TABLE[] = "0123456789abcdef";

void urlencode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    const unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)inbuf;
        while(pos < inlen && index < outlen){
            if(('a' <= buf[pos] && buf[pos] <= 'z') || ('A' <= buf[pos] && buf[pos] <= 'Z') || ('0' <= buf[pos] && buf[pos] <= '9')){
                outbuf[index++] = tolower(buf[pos++]);
            }
            else{
                outbuf[index++] = '%';
                outbuf[index++] = TABLE[tolower(buf[pos]) >> 4];
                outbuf[index++] = TABLE[tolower(buf[pos++]) & 15];
            };
        }
        outbuf[index] = '\0';
    }
}

void urldecode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)outbuf;
        while(pos < inlen && index < outlen){
            buf[index++] = ((int)(strchr(TABLE, tolower(inbuf[pos + 1])) - TABLE) << 4) | (int)(strchr(TABLE, tolower(inbuf[pos + 2])) - TABLE);
            pos += 3;
        }
        buf[index] = '\0';
    }
}
