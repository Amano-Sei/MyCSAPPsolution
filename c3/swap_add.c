/*************************************************************************
    > File Name: swap_add.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月05日 星期四 11时27分17秒
 ************************************************************************/

#include<stdio.h>

long swap_add(long *xp, long *yp){
    long x = *xp;
    long y = *yp;
    *xp = y;
    *yp = x;
    return x+y;
}

long call(){
    long arg1 = 534;
    long arg2 = 1057;
    long sum = swap_add(&arg1, &arg2);
    long diff = arg1 - arg2;
    return sum * diff;
}

