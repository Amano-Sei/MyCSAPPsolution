/*************************************************************************
    > File Name: tmult_ok2.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 15时47分05秒
 ************************************************************************/

#include <stdio.h>

int tmult_ok2(long x, long y, long *dest){
    int result;
    *dest = x*y;
    asm("setae %%bl\n\t"
        "movzbl %%bl, %[val]"
        : [val] "=r" (result)
        :
        : "%bl"
        );
    return result;
}

