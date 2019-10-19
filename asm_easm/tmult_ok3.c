/*************************************************************************
    > File Name: tmult_ok3.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 16时14分37秒
 ************************************************************************/

#include <stdio.h>

int tmult_ok3(long x, long y, long *dest){
    unsigned char bresult;
    *dest = x*y;
    asm("setae %[b]"
        : [b] "=r" (bresult)
        );
    return (int)bresult;
}

