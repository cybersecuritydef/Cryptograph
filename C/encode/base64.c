#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void b64encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t index = 0;
    size_t pos = 0;
    const unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (const unsigned char *)inbuf;
        while(pos < inlen && index < (outlen - 1)){
            if(index < (outlen - 1))
                outbuf[index++] = TABLE[(buf[pos] >> 2)];            
            if(index < (outlen - 1)){
                if(inlen - pos > 1)            
                    outbuf[index++] = TABLE[(((buf[pos] & 3) << 4) | (buf[pos + 1] >> 4))];
                else
                    outbuf[index++] = TABLE[(((buf[pos] & 3) << 4) | (0 >> 4))];
            }            
            if(index < (outlen - 1)){
                if((inlen - pos) > 1){
                    if((inlen - pos) > 2)
                        outbuf[index++] = TABLE[(((buf[pos + 1] & 15) << 2) | (buf[pos + 2] >> 6))];
                    else
                        outbuf[index++] = TABLE[(((buf[pos + 1] & 15) << 2) | (0 >> 6))];
                }                    
                else
                    outbuf[index++] = '=';
            }            
            if(index < (outlen - 1)){
                if((inlen - pos) > 2)
                    outbuf[index++] = TABLE[(buf[pos + 2] & 63)];
                else
                    outbuf[index++] = '=';
            }            
            pos += 3;
        }
        outbuf[index] = '\0';
    }
}

void b64decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen){
    size_t pos = 0;
    size_t index = 0;
    const char *p0 = NULL;
    const char *p1 = NULL;
    const char *p2 = NULL;
    const char *p3 = NULL;
    unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL && outlen > 0){
        buf = (unsigned char *)outbuf;
        while(pos < inlen && index < (outlen - 1)){
            if((p0 = strchr(TABLE, inbuf[pos])) == NULL || (p1 = strchr(TABLE, inbuf[pos + 1])) == NULL)
                break;
            buf[index++] = ((int)(p0 - TABLE) << 2) | ((int)(p1 - TABLE) >> 4);
            if(index < (outlen - 1) && inbuf[pos + 2] != '='){
                if((p2 = strchr(TABLE, inbuf[pos + 2])) == NULL)
                    break;
                buf[index++] = (((int)(p1 - TABLE) & 15) << 4) | ((int)(p2 - TABLE) >> 2);
                if(index < (outlen - 1) && inbuf[pos + 3] != '='){
                    if((p3 = strchr(TABLE, inbuf[pos + 3])) == NULL)
                        break;
                    buf[index++] = (((int)(p2 - TABLE) & 3) << 6) | (int)(p3 - TABLE);
                }
            }
            pos += 4;
        }
        buf[index] = '\0';
    }
}
