/*************************************************************************
    > File Name: 3_58.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 14时02分25秒
 ************************************************************************/

#include<stdio.h>

long decode2(long x, long y, long z){
    y = y-z;
    return (y<<63>>63) ^ (x*y);
}

