/*************************************************************************
    > File Name: pp6.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月21日 星期一 15时03分29秒
 ************************************************************************/

#include <stdio.h>

#define VBYTES 32
#define VSIZE VBYTES/sizeof(double)

typedef double vec_t __attribute__((vector_size(VBYTES)));

//没想太多，直接vector 4*4展开好了
//至于向量的cpe不知道各种参数...不会算（

double poly(double a[], double x, long degree){
    long i;
    long cnt = degree+1;
    double result = 0;
    double xpwr = 1;
    while((long)a % VBYTES != 0 && cnt){
        result = result + *a++ * xpwr;
        xpwr = xpwr*x;
        cnt--;
    }
    vec_t asum = {0};
    vec_t asum1 = {0};
    vec_t asum2 = {0};
    vec_t asum3 = {0};
    vec_t xs = { 1, x, x*x, x*x*x };
    double x4 = xs[3]*x;
    xs *= xpwr;
    vec_t xs1 = xs*x4;
    vec_t xs2 = xs1*x4;
    vec_t xs3 = xs2*x4;
    double x16 = x4*x4*x4*x4;
    while(cnt >= 4*VSIZE){
        vec_t chunk = *(vec_t *)a;
        asum = asum + chunk*xs;
        chunk = *(vec_t *)(a+VSIZE);
        asum1 = asum1 + chunk*xs1;
        chunk = *(vec_t *)(a+2*VSIZE);
        asum2 = asum2 + chunk*xs2;
        chunk = *(vec_t *)(a+3*VSIZE);
        asum3 = asum3 + chunk*xs3;
        xs *= x16;
        xs1 *= x16;
        xs2 *= x16;
        xs3 *= x16;
        a += 4*VSIZE;
        cnt -= 4*VSIZE;
    }
    while(cnt >= VSIZE){
        vec_t chunk = *(vec_t *)a;
        asum = asum + chunk*xs;
        xs *= x4;
        a += VSIZE;
        cnt -= VSIZE;
    }
    xpwr = xs[0];
    while(cnt){
        result = result + *a++ * xpwr;
        xpwr *= x;
        cnt--;
    }
    asum = (asum+asum1)+(asum2+asum3);
    for(i = 0; i < VSIZE; i++)
        result += asum[i];
    return result;
}


