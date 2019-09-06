/*************************************************************************
    > File Name: tunion.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月06日 星期五 15时02分15秒
 ************************************************************************/

#include<stdio.h>

union {
    double d;
    long u;
}tmp;

int main(){
    tmp.d = -0.0;
    printf("%llx", tmp.u);
}

