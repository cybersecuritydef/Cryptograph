#ifndef __URLENCODE_H__
#define __URLENCODE_H__

/* size buffer urlencode  strlen(string) * 3 + 1
   size buffer urldecode strlen(string) / 3 + 1
*/

void urlencode(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen);

void urldecode(const char *inbuf, const size_t inlen, void *outbuf, const size_t outlen);

#endif
