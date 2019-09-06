/*************************************************************************
    > File Name: switch_eg.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月03日 星期二 18时45分30秒
 ************************************************************************/

#include<stdio.h>

void switch_eg(long x, long n, long *dest){
    long val = x;
    switch(n){
        case 100:
            val *= 13;
            break;
        case 102:
            val += 10;
        case 103:
            val += 11;
            break;
        case 104:
        case 106:
            val *= val;
            break;
        default:
            val = 0;
    }
    *dest = val;
}

