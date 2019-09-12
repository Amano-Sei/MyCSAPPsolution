/*************************************************************************
    > File Name: 3_68.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 22时18分06秒
 ************************************************************************/

#include <stdio.h>

#define A 9
#define B 5

typedef struct{
    int x[A][B];
    long y;
}str1;

typedef struct{
    char array[B];
    int t;
    short s[A];
    long u;
}str2;

void setVal(str1 *p, str2 *q){
    long v1 = q->t;
    long v2 = q->u;
    p->y = v1+v2;
}

