/*************************************************************************
    > File Name: tfcmp.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月09日 星期一 22时50分05秒
 ************************************************************************/

#include<stdio.h>

void tfcmp1(double a, double b, int *ans){
    while(a-b < 0){
        a += 1.0;
        (*ans)++;
    }
}

void tfcmp2(double a, double b, int *ans){
    while(a <= b){
        a += 1.0;
        (*ans)++;
    }
}

void tfcmp3(double a, double b, double *c, int *ans){
    while(a == b){
        a += 1.0;
        b = *c++;
        (*ans)++;
    }
}

void tfcmp4(double a, double b, int *ans){
    while(a >= b){
        a += 1.0;
        (*ans)++;
    }
}

void tfcmp5(double a, double b, int *ans){
    while(a > b){
        a += 1.0;
        (*ans)++;
    }
}

void tlcmp(long a, long b, int *ans){
    while(a - b > 0){
        a += 1.0;
        (*ans)++;
    }
}

