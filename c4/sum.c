/*************************************************************************
    > File Name: sum.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月19日 星期四 17时11分04秒
 ************************************************************************/

#include <stdio.h>

long sum(long *start, long count){
    long sum = 0;
    while(count){
        sum += *start;
        start++;
        count--;
    }
    return sum;
}

