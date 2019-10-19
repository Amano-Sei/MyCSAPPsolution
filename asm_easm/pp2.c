/*************************************************************************
    > File Name: pp2.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 19时41分08秒
 ************************************************************************/

#include <stdio.h>

void umult_full(unsigned long x, unsigned long y, unsigned long *dest){
    asm("movq %[x] %%rax\n\t"
        "mulq %[y]\n\t"
        "movq %%rax %[lo]\n\t"
        "movq %%rdx %[hi]"
        : [lo] "=m" (dest[0]), [hi] "=m" (dest[1])
        : [x] "r" (x), [y] "r" (y)
        : "%rax", "%rdx"
        );
}

