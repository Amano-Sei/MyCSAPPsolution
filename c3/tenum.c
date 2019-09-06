/*************************************************************************
    > File Name: tenum.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月06日 星期五 14时38分58秒
 ************************************************************************/

#include<stdio.h>

enum dd {aa=1, bb=2, cc=3} desu;
int main(){
    for(desu = aa; desu != cc; desu++)
        printf("%d", desu);
    return 0;
}

