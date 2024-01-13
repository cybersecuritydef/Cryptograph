#ifndef __BASE16_H__
#define __BASE16_H__

/* size buffer encode  strlen(string) * 2 + 1
   size buffer decode strlen(string) / 2 + 1
*/

void b16encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen);

void b16decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen);

#endif
