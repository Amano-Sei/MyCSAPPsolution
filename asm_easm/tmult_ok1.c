/*************************************************************************
    > File Name: tmult_ok1.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 14时32分10秒
 ************************************************************************/

#include <stdio.h>

int tmult_ok1(long x, long y, long *dest){
    long result = 0;
    *dest = x*y;
    asm("setae %al");
    return result;
}

