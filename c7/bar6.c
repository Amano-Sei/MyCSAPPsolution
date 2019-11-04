/*************************************************************************
    > File Name: bar6.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月31日 星期四 18时02分01秒
 ************************************************************************/

#include <stdio.h>

unsigned y;
unsigned x;

void f(){
    x = 0;
    y = 0x7ff00000;
    printf("x at %p %x, y at %p %x\n", &x, x, &y, y);
}

