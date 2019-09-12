/*************************************************************************
    > File Name: fcvt.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月09日 星期一 20时53分32秒
 ************************************************************************/

#include<stdio.h>

double fcvt(int i, float *fp, double *dp, long *lp){
    float f = *fp;
    double d = *dp;
    long l = *lp;
    *lp = (long)d;
    *fp = (float)i;
    *dp = (double)l;
    return (double)f;
}

