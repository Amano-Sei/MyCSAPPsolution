/*************************************************************************
    > File Name: fact_while.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月03日 星期二 14时42分09秒
 ************************************************************************/

#include<stdio.h>

long fact_while(long n){
    long result = 1;
    while(n>1){
        result *= n;
        n = n-1;
    }
    return result;
}

