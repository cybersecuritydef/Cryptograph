#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char TABLE[] = "0123456789ABCDEF";

void encode(const char *plain, char *urlenc, const size_t len){
    if(plain != NULL && urlenc != NULL && len >= strlen(plain)){
        while(*plain != '\0'){
            *urlenc++ = TABLE[*plain >> 4];
            *urlenc++ = TABLE[*plain++ & 15];
        }
        *urlenc = '\0';
    }
}

void decode(const char *encoded, size_t encoded_len, char *plain, size_t plain_len){
    size_t pos = 0;
    size_t index = 0;
    if(encoded_len > 0 && plain_len > 0){
        while(pos < encoded_len){
            plain[index++] = ((int)(strchr(TABLE, encoded[pos]) - TABLE) << 4) | (int)(strchr(TABLE, encoded[pos + 1]) - TABLE);
            pos += 2;
        }
        plain[index] = '\0';
    }
}
