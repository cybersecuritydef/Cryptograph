#ifndef __MD2_H__
#define __MD2_H__

#define MD2_BLOCK_SIZE 16

int digest(char *plain, size_t plain_len, unsigned char *digest, size_t *digest_len);

#endif
