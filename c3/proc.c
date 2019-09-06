/*************************************************************************
    > File Name: proc.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月05日 星期四 10时56分53秒
 ************************************************************************/

#include<stdio.h>

void proc(long a1, long *a1p,
          int a2, int *a2p,
          short a3, short *a3p,
          char a4, char *a4p){
    *a1p += a1;
    *a2p += a2;
    *a3p += a3;
    *a4p += a4;
}

