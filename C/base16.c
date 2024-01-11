#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char TABLE[] = "0123456789ABCDEF";

void b16encode(const char *plain, char *encoded, const size_t len){
    if(plain != NULL && encoded != NULL && len >= strlen(plain)){
        while(*plain != '\0'){
            *encoded++ = TABLE[*plain >> 4];
            *encoded++ = TABLE[*plain++ & 15];
        }
        *encoded = '\0';
    }
}

void b16decode(const char *encoded, char *plain, const size_t len){
    if(encoded != NULL && plain != NULL && len >= strlen(encoded)){
        while(*encoded != '\0'){
            *plain++ = ((int)(strchr(TABLE, *encoded) - TABLE) << 4) | (int)(strchr(TABLE, *(encoded + 1)) - TABLE);
            *(encoded += 2);
        }
        *plain = '\0';
    }
}
