/*************************************************************************
    > File Name: pp1.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 19时20分24秒
 ************************************************************************/

#include <stdio.h>

int tmult_ok(long x, long y, long *dest){
    unsigned char bresult;
    asm("imulq %[x], %[y]\n\t"
        "setae %[b]"
        :[y] "+r" (y), [b] "=r" (bresult)
        :[x] "r" (x)
        );
    *dest = y;
    return bresult;
}

