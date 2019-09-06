/*************************************************************************
    > File Name: mstore.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月31日 星期六 21时09分22秒
 ************************************************************************/

#include<stdio.h>

long mult2(long, long);
void multstore(long x, long y, long *dest){
    long t = mult2(x, y);
    *dest = t;
}

