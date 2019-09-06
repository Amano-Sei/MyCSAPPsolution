/*************************************************************************
    > File Name: absdiff_se.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月02日 星期一 17时27分43秒
 ************************************************************************/

#include<stdio.h>

long lt_cnt = 0;
long ge_cnt = 0;

long absdiff_se(long x, long y){
    long result;
    if(x < y){
        lt_cnt++;
        result = y-x;
    }else{
        ge_cnt++;
        result = x-y;
    }
    return result;
}

