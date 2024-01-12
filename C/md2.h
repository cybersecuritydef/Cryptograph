#ifndef __MD2_H__
#define __MD2_H__

#define MD2_BLOCK_SIZE 16

int md2(const unsigned char *inbuf, size_t inlen, unsigned char *outbuf, size_t outlen);

#endif
