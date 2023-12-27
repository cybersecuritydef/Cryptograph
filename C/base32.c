#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char TABLE[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567";

void encode(const char *plain, size_t plain_len, char *encoded, size_t encoded_len){
    size_t pos = 0;
    size_t index = 0;
    if(plain_len > 0 && encoded_len > 0){
        while(pos < plain_len){
            encoded[index++] = TABLE[(plain[pos] >> 3) & 31];
            encoded[index++] = TABLE[((plain[pos] << 2) | (plain[pos + 1] >> 6)) & 31];
            if((plain_len - pos) > 1)
                encoded[index++] = TABLE[((plain[pos + 1] >> 1) & 31)];
            else
                encoded[index++] = '=';

            if((plain_len - pos) > 1)
                encoded[index++] = TABLE[((plain[pos + 1] << 4) | (plain[pos + 2] >> 4)) & 31];
            else
                encoded[index++] = '=';

            if((plain_len - pos) > 2)
                encoded[index++] = TABLE[((plain[pos + 2] << 1) | (plain[pos + 3] >> 7)) & 31];
            else
                encoded[index++] = '=';

            if((plain_len - pos) > 3)
                encoded[index++] = TABLE[(plain[pos + 3] >> 2) & 31];
            else
                encoded[index++] = '=';

            if((plain_len - pos) > 3)
                encoded[index++] = TABLE[((plain[pos + 3] << 3) | (plain[pos + 4] >> 5)) & 31];
            else
                encoded[index++] = '=';

            if((plain_len - pos) > 4)
                encoded[index++] = TABLE[(plain[pos + 4] & 31)];
            else
                encoded[index++] = '=';
            pos += 5;
        }
        encoded[index] = '\0';
    }
}

void decode(const char *encoded, size_t encoded_len, char *plain, size_t plain_len){
    size_t pos = 0;
    size_t index = 0;
    if(encoded_len > 0 && plain_len > 0){
        while(pos < encoded_len){
            plain[index++] = ((int)(strchr(TABLE, encoded[pos]) - TABLE) << 3) | ((int)(strchr(TABLE, encoded[pos + 1]) - TABLE) >> 2);
            if(encoded[pos + 2] != '=')
                plain[index++] = ((int)(strchr(TABLE, encoded[pos + 1]) - TABLE) << 6) | ((int)(strchr(TABLE, encoded[pos + 2]) - TABLE) << 1) | ((int)(strchr(TABLE, encoded[pos + 3]) - TABLE) >> 4);
            if(encoded[pos + 4] != '=')
                plain[index++] = ((int)(strchr(TABLE, encoded[pos + 3]) - TABLE) << 4) | ((int)(strchr(TABLE, encoded[pos + 4]) - TABLE) >> 1);
            if(encoded[pos + 5] != '=')
                plain[index++] = ((int)(strchr(TABLE, encoded[pos + 4]) - TABLE) << 7) | ((int)(strchr(TABLE, encoded[pos + 5]) - TABLE) << 2) | ((int)(strchr(TABLE, encoded[pos + 6]) - TABLE) >> 3);
            if(encoded[pos + 7] != '=')
                plain[index++] = ((int)(strchr(TABLE, encoded[pos + 6]) - TABLE) << 5) | (int)(strchr(TABLE, encoded[pos + 7]) - TABLE);
            pos += 8;
        }
        plain[index] = '\0';
    }
}
