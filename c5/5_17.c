/*************************************************************************
    > File Name: 5_17.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月20日 星期日 16时21分12秒
 ************************************************************************/

#include <stdio.h>
#define K sizeof(unsigned long)

void *mymemset(void *s, int c, size_t n){
    unsigned char *schar = (unsigned char *)s;
    unsigned long lc = (unsigned char)c;
    for(int i = 1; i < K; i++)
        lc = (lc<<8)|(unsigned char)c;
    while((unsigned long)schar % K != 0 && n != 0){
        *schar++ = (unsigned char)c;
        n--;
    }
    while(n >= K){
        *(unsigned long *)schar = lc;
        schar += K;
        n -= K;
    }
    while(n != 0){
        *schar++ = (unsigned char)c;
        n--;
    }
    return s;
}

