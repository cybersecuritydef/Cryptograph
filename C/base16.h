#ifndef __BASE16_H__
#define __BASE16_H__


void encode(const char *plain, char *encoded, const size_t len);

void decode(const char *encoded, char *plain, const size_t len);

#endif
