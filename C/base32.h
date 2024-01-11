#ifndef __BASE32_H__
#define __BASE32_H__


void b32encode(const char *plain, size_t plain_len, char *encoded, size_t encoded_len);

void b32decode(const char *encoded, size_t encoded_len, char *plain, size_t plain_len);

#endif
