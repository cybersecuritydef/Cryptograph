#ifndef __MD2_H__
#define __MD2_H__

#define MD2_BLOCK_SIZE 16

void md2(const void *inbuf, const size_t inlen, char *outbuf, const size_t outlen);

#endif
