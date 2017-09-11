#ifndef PS_SHA_256_H_INCLUDED
#define PS_SHA_256_H_INCLUDED


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
void initilize(SHA2 *ptr);
void update(SHA2 *ptr, const uc data[], size_t len);
void data_final(SHA2 *ptr, uc hash[]);
void print_hash(uc hash[]);


#endif // PS_SHA_256_H_INCLUDED
