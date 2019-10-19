/*************************************************************************
    > File Name: pp5.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月12日 星期四 10时55分53秒
 ************************************************************************/

#include <stdio.h>

double dmin(double x, double y){
    double ans;
    asm("vminsd %[x], %[y], %[ans]"
        : [ans] "=x" (ans)
        : [x] "x" (x), [y] "x" (y));
    return ans;
}

