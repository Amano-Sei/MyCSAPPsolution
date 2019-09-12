/*************************************************************************
    > File Name: 3_65.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 19时07分02秒
 ************************************************************************/

#include<stdio.h>
#define M 15

void transpose(long A[M][M]){
    long i, j;
    for(i = 0; i < M; i++)
        for(j = 0; j < i; j++){
            long t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
}

