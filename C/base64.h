#ifndef __BASE64_H__
#define __BASE64_H__


void b64encode(const char *plain, size_t plain_len, char *encoded, size_t encoded_len);

void b64decode(const char *encoded, size_t encoded_len, char *plain, size_t plain_len);

#endif
