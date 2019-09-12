/*************************************************************************
    > File Name: tmult_ok_asm.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 13时53分13秒
 ************************************************************************/

#include <stdio.h>

int tmult_ok_asm(long x, long y, long *dest){
    long p = x*y;
    *dest = p;
    return p > 0;
}

