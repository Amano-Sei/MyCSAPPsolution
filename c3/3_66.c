/*************************************************************************
    > File Name: 3_66.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 19时57分42秒
 ************************************************************************/

#include<stdio.h>
#define NR(x) 3*x
#define NC(x) 4*x+1

long sum_col(long n, long A[NR(n)][NC(n)], long j){
    long i;
    long result = 0;
    for(i = 0; i < NR(n); i++)
        result += A[i][j];
    return result;
}

