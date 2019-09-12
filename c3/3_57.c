/*************************************************************************
    > File Name: 3_57.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月09日 星期一 23时39分07秒
 ************************************************************************/

#include<stdio.h>

double funct3(int *ap, double b, long c, float *dp){
    float d = *dp;
    if(b > *ap)
        return d+d+c;
    else
        return d*c;
}

