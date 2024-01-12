#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void b64encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    const unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL && outlen > inlen){
        buf = (unsigned char *)inbuf;
        while(pos < inlen){
            outbuf[index++] = TABLE[(buf[pos] >> 2)];
            outbuf[index++] = TABLE[(((buf[pos] & 3) << 4) | (buf[pos + 1] >> 4))];
            if((inlen - pos) > 1)
                outbuf[index++] = TABLE[(((buf[pos + 1] & 15) << 2) | (buf[pos + 2] >> 6))];
            else
                outbuf[index++] = '=';
            if((inlen - pos) > 2)
                outbuf[index++] = TABLE[(buf[pos + 2] & 63)];
            else
                outbuf[index++] = '=';
            pos += 3;
        }
        outbuf[index] = '\0';
    }
}

void b64decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen){
    size_t pos = 0;
    size_t index = 0;
    unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)outbuf;
        while(pos < inlen){
            buf[index++] = ((int)(strchr(TABLE, inbuf[pos]) - TABLE) << 2) | ((int)(strchr(TABLE, inbuf[pos + 1]) - TABLE) >> 4);
            if(inbuf[pos + 2] != '=')
                buf[index++] = (((int)(strchr(TABLE, inbuf[pos + 1]) - TABLE) & 15) << 4) | ((int)(strchr(TABLE, inbuf[pos + 2]) - TABLE) >> 2);
            if(inbuf[pos + 3] != '=')
                buf[index++] = (((int)(strchr(TABLE, inbuf[pos + 2]) - TABLE) & 3) << 6) | (int)(strchr(TABLE, inbuf[pos + 3]) - TABLE);
            pos += 4;
        }
        buf[index] = '\0';
    }
}
