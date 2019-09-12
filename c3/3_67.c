/*************************************************************************
    > File Name: 3_67.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 20时10分12秒
 ************************************************************************/

#include<stdio.h>

typedef struct{
    long a[2];
    long *p;
}strA;

typedef struct{
    long u[2];
    long q;
}strB;

strB process(strA s){
    strB r;
    r.u[0] = s.a[1];
    r.u[1] = s.a[0];
    r.q = *s.p;
    return r;
}

long eval(long x, long y, long z){
    strA s;
    s.a[0] = x;
    s.a[1] = y;
    s.p = &z;
    strB r = process(s);
    return r.u[0]+r.u[1]+r.q;
}

