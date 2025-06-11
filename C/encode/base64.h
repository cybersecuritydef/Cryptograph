#ifndef __BASE64_H__
#define __BASE64_H__

/* size buffer encode  (strlen(string) + 2) / 3 * 4
   size buffer decode (strlen(string) / 4) * 3
*/
void b64encode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen);

void b64decode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen);

#endif
