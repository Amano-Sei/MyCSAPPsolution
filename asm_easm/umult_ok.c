/*************************************************************************
    > File Name: umult_ok.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 18时59分14秒
 ************************************************************************/

#include <stdio.h>

int umult_ok(unsigned long x, unsigned long y, unsigned long *dest){
    unsigned char bresult;

    asm("movq %[x], %%rax\n\t"
        "mulq %[y]\n\t"
        "movq %%rax, %[p]\n\t"
        "setae %[b]"
        : [p] "=m" (*dest), [b] "=r" (bresult)
        : [x] "r" (x), [y] "r" (y)
        : "%rax", "%rdx"
        );

    return (int)bresult;
}

