/*************************************************************************
    > File Name: 3_9.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月01日 星期日 19时05分24秒
 ************************************************************************/

#include<stdio.h>

long shift_left4_rightn(long x, long n){
    x<<=4;
    x>>=n;
    return x;
}

