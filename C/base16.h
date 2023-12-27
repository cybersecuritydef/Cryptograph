#ifndef __BASE16_H__
#define __BASE16_H__


void encode(const char *plain, size_t plain_len, char *encoded, size_t encoded_len);

void decode(const char *encoded, size_t encoded_len, char *plain, size_t plain_len);

#endif
