#ifndef __BASE16_H__
#define __BASE16_H__


void b16encode(const char *plain, char *encoded, const size_t len);

void b16decode(const char *encoded, char *plain, const size_t len);

#endif
