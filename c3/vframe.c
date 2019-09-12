/*************************************************************************
    > File Name: vframe.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月09日 星期一 17时52分15秒
 ************************************************************************/

#include<stdio.h>

long vframe(long n, long idx, long *q){
    long i;
    long *p[n];
    p[0] = &i;
    for(int i = 0; i < n; i++)
        p[i] = q;
    return *p[idx];
}

