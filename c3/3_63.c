/*************************************************************************
    > File Name: 3_63.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 18时19分01秒
 ************************************************************************/

#include<stdio.h>

long switch_prob(long x, long n){
    long result = x;
    switch(n){
        case 60:
        case 62:
            result = 8*x;
            break;
        case 63:
            result = x>>3;
            break;
        case 64:
            x = 15*x;
        case 65:
            x = x*x;
        default:
            result = x+0x4b;
    }
    return result;
}

