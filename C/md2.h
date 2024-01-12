#ifndef __MD2_H__
#define __MD2_H__

#define MD2_BLOCK_SIZE 16

void digest(const void *inbuf, const size_t inlen, void *outbuf, const size_t outlen);

#endif
