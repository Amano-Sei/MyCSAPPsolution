/*************************************************************************
    > File Name: 5_12.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月18日 星期五 15时02分53秒
 ************************************************************************/

#include <stdio.h>

void psum1(float a[], float p[], long n){
    long i;
    float t = 0.0;
    for(i = 0; i < n; i++)
        p[i] = (t+=a[i]);
}

