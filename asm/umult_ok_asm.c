/*************************************************************************
    > File Name: umult_ok_asm.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 14时13分42秒
 ************************************************************************/

#include <stdio.h>

int umult_ok_asm(unsigned long x, unsigned long y, unsigned long *dest){
    unsigned long p = x*y;
    *dest = p;
    return p > 0;
}

