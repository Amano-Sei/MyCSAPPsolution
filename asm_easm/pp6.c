/*************************************************************************
    > File Name: pp6.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月12日 星期四 11时01分56秒
 ************************************************************************/

#include <stdio.h>

double dsqrt(double x){
    double ans;
    asm("sqrtsd %[x], %[ans]"
        : [ans] "=x" (ans)
        : [x] "x" (x));
    return ans;
    //相较于上面的代码，下面的c代码更短但是生成了三条汇编指令...
    //asm("sqrtsd %[cx], %[cx]"
    //    : [cx] "+x" (x));
    //return x;
}

