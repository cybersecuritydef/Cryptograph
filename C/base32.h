#ifndef __BASE32_H__
#define __BASE32_H__

/* size buffer encode  (8 * ((strlen(string) + 4) / 5)) + 1
   size buffer decode (strlen(string) * 5) / 5
*/

void b32encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen);

void b32decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen);

#endif
