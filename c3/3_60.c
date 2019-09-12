/*************************************************************************
    > File Name: 3_60.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 14时55分12秒
 ************************************************************************/

#include<stdio.h>

long loop(long x, int n){
    long result = 0;
    long mask;
    for(mask = 1; mask != 0; mask = mask << n){
        result |= x & mask;
    }
    return result;
}

