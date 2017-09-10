#ifndef SHA256_H_INCLUDED
#define SHA256_H_INCLUDED


/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 uc digest

/**************************** DATA TYPES ****************************/
typedef unsigned char uc;             // 8-bit uc
typedef unsigned int  ui;             // 32-bit ui, change to "long" for 16-bit machines

typedef struct {
	uc data[64];
	ui datalen;
	unsigned long long bitlen;
	ui state[8];
} SHA2;

/*********************** FUNCTION DECLARATIONS **********************/
void sha256_init(SHA2 *ptr);
void sha256_update(SHA2 *ptr, const uc data[], size_t len);
void sha256_final(SHA2 *ptr, uc hash[]);


#endif // SHA256_H_INCLUDED
