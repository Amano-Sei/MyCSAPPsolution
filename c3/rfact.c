/*************************************************************************
    > File Name: rfact.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月05日 星期四 13时31分02秒
 ************************************************************************/

#include<stdio.h>

long rfact(long n){
    long result;
    if(n <= 1)
        result = 1;
    else
        result = n * rfact(n-1);
    return result;
}

