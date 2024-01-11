#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void b64encode(const char *plain, size_t plain_len, char *encoded, size_t encoded_len){
    size_t index = 0;
    size_t pos = 0;
    if(plain_len > 0 && encoded_len > 0){
        while(pos < plain_len){
            encoded[index++] = TABLE[(plain[pos] >> 2)];
            encoded[index++] = TABLE[(((plain[pos] & 3) << 4) | (plain[pos + 1] >> 4))];
            if((plain_len - pos) > 1)
                encoded[index++] = TABLE[(((plain[pos + 1] & 15) << 2) | (plain[pos + 2] >> 6))];
            else
                encoded[index++] = '=';
            if((plain_len - pos) > 2)
                encoded[index++] = TABLE[(plain[pos + 2] & 63)];
            else
                encoded[index++] = '=';
            pos += 3;
        }
        encoded[index] = '\0';
    }
}

void b64decode(const char *encoded, size_t encoded_len, char *plain, size_t plain_len){
    size_t pos = 0;
    size_t index = 0;
    if(encoded_len > 0 && plain_len > 0){
        while(pos < encoded_len){
            plain[index++] = ((int)(strchr(TABLE, encoded[pos]) - TABLE) << 2) | ((int)(strchr(TABLE, encoded[pos + 1]) - TABLE) >> 4);
            if(encoded[pos + 2] != '=')
                plain[index++] = (((int)(strchr(TABLE, encoded[pos + 1]) - TABLE) & 15) << 4) | ((int)(strchr(TABLE, encoded[pos + 2]) - TABLE) >> 2);
            if(encoded[pos + 3] != '=')
                plain[index++] = (((int)(strchr(TABLE, encoded[pos + 2]) - TABLE) & 3) << 6) | (int)(strchr(TABLE, encoded[pos + 3]) - TABLE);
            pos += 4;
        }
        plain[index] = '\0';
    }
}
