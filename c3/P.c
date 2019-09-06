/*************************************************************************
    > File Name: P.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月05日 星期四 12时47分23秒
 ************************************************************************/

#include<stdio.h>

long Q(long);

long P(long x, long y){
    long u = Q(x);
    long v = Q(y);
    return u+v;
}

