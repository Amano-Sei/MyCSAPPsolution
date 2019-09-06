/*************************************************************************
    > File Name: fix_prod_ele.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月05日 星期四 16时47分55秒
 ************************************************************************/

#include<stdio.h>

#define N 16
typedef int fix_matrix[N][N];

int fix_prod_ele(fix_matrix A, fix_matrix B, long i, long k){
    long j;
    int result = 0;
    for(j = 0; j < N; j++)
        result += A[i][j]*B[j][k];
    return result;
}

