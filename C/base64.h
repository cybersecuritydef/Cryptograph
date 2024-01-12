#ifndef __BASE64_H__
#define __BASE64_H__

/* size buffer encode  (4 * ((strlen(string) + 2) / 3)) + 1
   size buffer decode (strlen(string) * 3) / 4
*/
void b64encode(const unsigned char *inbuf, const size_t inlen, char *outbuf, const size_t outlen);

void b64decode(const char *inbuf, const size_t inlen, unsigned char *outbuf, const size_t outlen);

#endif
