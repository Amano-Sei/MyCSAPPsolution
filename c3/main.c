/*************************************************************************
    > File Name: main.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月31日 星期六 21时51分30秒
 ************************************************************************/

#include<stdio.h>

void multstore(long, long, long *);
int main(){
    long d;
    multstore(2, 3, &d);
    printf("2 * 3 --> %ld\n", d);
    return 0;
}
long mult2(long a, long b){
    long s = a * b;
    return s;
}

