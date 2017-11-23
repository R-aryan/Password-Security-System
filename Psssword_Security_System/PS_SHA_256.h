#ifndef PS_SHA_256_H_INCLUDED
#define PS_SHA_256_H_INCLUDED


/*************************** HEADER FILES ***************************/
#include <stddef.h>

/****************************** MACROS ******************************/
#define SHA256_BLOCK_SIZE 32            // SHA256 outputs a 32 uc digest

/**************************** DATA TYPES ****************************/
typedef unsigned char uc;             // 8-bit uc
typedef unsigned int  ui;             // 32-bit ui, change to "long" for 16-bit machines

/*
The unsigned char simply means: Use the most significant bit instead of treating it as a bit flag for +/- sign
 when performing arithmetic operations.
It makes significance if you use char as a number for instance:

typedef char BYTE1;
typedef unsigned char BYTE2;

BYTE1 a;
BYTE2 b;
For variable a, only 7 bits are available and its range is (-127 to 127) = (+/-)2^7 -1.
For variable b all 8 bits are available and the range is 0 to 255 (2^8 -1).

If you use char as character, "unsigned" is completely ignored by the compiler just as comments are removed from your program.

*/
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
uc* print_hash(uc hash[]);


#endif // PS_SHA_256_H_INCLUDED
