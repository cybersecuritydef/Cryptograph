#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

void b32encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen){
    size_t pos = 0;
    size_t index = 0;
    const unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)inbuf;
        while(pos < inlen && index < outlen){
            outbuf[index++] = TABLE[(buf[pos] >> 3) & 31];
            outbuf[index++] = TABLE[((buf[pos] << 2) | (buf[pos + 1] >> 6)) & 31];
            if((inlen - pos) > 1)
                outbuf[index++] = TABLE[((buf[pos + 1] >> 1) & 31)];
            else
                outbuf[index++] = '=';

            if((inlen - pos) > 1)
                outbuf[index++] = TABLE[((buf[pos + 1] << 4) | (buf[pos + 2] >> 4)) & 31];
            else
                outbuf[index++] = '=';

            if((inlen - pos) > 2)
                outbuf[index++] = TABLE[((buf[pos + 2] << 1) | (buf[pos + 3] >> 7)) & 31];
            else
                outbuf[index++] = '=';

            if((inlen - pos) > 3)
                outbuf[index++] = TABLE[(buf[pos + 3] >> 2) & 31];
            else
                outbuf[index++] = '=';

            if((inlen - pos) > 3)
                outbuf[index++] = TABLE[((buf[pos + 3] << 3) | (buf[pos + 4] >> 5)) & 31];
            else
                outbuf[index++] = '=';

            if((inlen - pos) > 4)
                outbuf[index++] = TABLE[(buf[pos + 4] & 31)];
            else
                outbuf[index++] = '=';
            pos += 5;
        }
        outbuf[index] = '\0';
    }
}

void b32decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen){
    size_t pos = 0;
    size_t index = 0;
    unsigned char *buf = NULL;
    if(inbuf != NULL && outbuf != NULL){
        buf = (unsigned char *)outbuf;
        while(pos < inlen && index < outlen){
            buf[index++] = ((int)(strchr(TABLE, inbuf[pos]) - TABLE) << 3) | ((int)(strchr(TABLE, inbuf[pos + 1]) - TABLE) >> 2);
            if(inbuf[pos + 2] != '=')
                buf[index++] = ((int)(strchr(TABLE, inbuf[pos + 1]) - TABLE) << 6) | ((int)(strchr(TABLE, inbuf[pos + 2]) - TABLE) << 1) | ((int)(strchr(TABLE, inbuf[pos + 3]) - TABLE) >> 4);
            if(inbuf[pos + 4] != '=')
                buf[index++] = ((int)(strchr(TABLE, inbuf[pos + 3]) - TABLE) << 4) | ((int)(strchr(TABLE, inbuf[pos + 4]) - TABLE) >> 1);
            if(inbuf[pos + 5] != '=')
                buf[index++] = ((int)(strchr(TABLE, inbuf[pos + 4]) - TABLE) << 7) | ((int)(strchr(TABLE, inbuf[pos + 5]) - TABLE) << 2) | ((int)(strchr(TABLE, inbuf[pos + 6]) - TABLE) >> 3);
            if(inbuf[pos + 7] != '=')
                buf[index++] = ((int)(strchr(TABLE, inbuf[pos + 6]) - TABLE) << 5) | (int)(strchr(TABLE, inbuf[pos + 7]) - TABLE);
            pos += 8;
        }
        buf[index] = '\0';
    }
}
