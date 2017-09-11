#include<stdio.h>
#include<memory.h>
#include<string.h>
#include "PS_SHA_256.h"

#define MAX_LIMIT 1000

int main()
{
    uc text1[MAX_LIMIT],hash[32];
    printf("Enter your data yo be hashed \n");
    gets(text1);

   //uc text1[]={"abc"},hash[32];
                 //text2[]={"abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"},
                 //text3[]={"aaaaaaaaaa"},

   int idx;
   SHA2 ptr;

   // Hash one
   initilize(&ptr);
   update(&ptr,text1,strlen(text1));
   data_final(&ptr,hash);
   print_hash(hash);

   // Hash two
   //initilize(&ptr);
   //update(&ptr,text2,strlen(text2));
   //data_final(&ptr,hash);
   //print_hash(hash);

   // Hash three
   //initilize(&ptr);
   //for(idx=0; idx < 100000; ++idx)
       //update(&ptr,text1,strlen(text1));
   //data_final(&ptr,hash);
   //print_hash(hash);

   getchar();
   return 0;
}
