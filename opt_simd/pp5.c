/*************************************************************************
    > File Name: pp5.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月21日 星期一 14时05分43秒
 ************************************************************************/

#include <stdio.h>

#define VBYTES 32
#define VSIZE VBYTES/sizeof(double)

typedef double vec_t __attribute__((vector_size(VBYTES)));

double poly(double a[], double x, long degree){
    long i;
    double result = 0;
    double xpwr = 1;
    while((long)a % VBYTES != 0 && degree >= 0){
        result = result + *a++ * xpwr;
        xpwr = xpwr*x;
        degree--;
    }
    vec_t asum = {0};
    vec_t xs = { 1, x, x*x, x*x*x };
    double x4 = xs[3]*x;
    xs *= xpwr;
    while(degree >= VSIZE-1){
        vec_t achunk = *(vec_t *)a;
        asum = asum + achunk*xs;
        xs *= x4;
        a += VSIZE;
        degree -= VSIZE;
    }
    xpwr = xs[0];
    while(degree >= 0){
        result = result + *a++ * xpwr;
        xpwr *= x;
        degree--;
    }
        
    for(i = 0; i < VSIZE; i++)
        result += asum[i];
    return result;
}

