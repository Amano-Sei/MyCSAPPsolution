/*************************************************************************
    > File Name: 3_64.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 18时53分14秒
 ************************************************************************/

#include<stdio.h>
#define R 7
#define S 5
#define T 13

long A[R][S][T];

long store_ele(long i, long j, long k, long *dest){
    *dest = A[i][j][k];
    return sizeof(A);
}

