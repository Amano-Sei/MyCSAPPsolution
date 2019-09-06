/*************************************************************************
    > File Name: call_proc.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月05日 星期四 11时48分09秒
 ************************************************************************/

#include<stdio.h>

void proc(long, long *, int ,int *, short, short *, char, char *);

//void proc(long a1, long *a1p,
//          int a2, int *a2p,
//          short a3, short *a3p,
//          char a4, char *a4p){
//    *a1p += a1;
//    *a2p += a2;
//    *a3p += a3;
//    *a4p += a4;
//}

long call_proc(){
    long x1 = 1;
    int x2 = 2;
    short x3 = 3;
    char x4 = 4;
    proc(x1, &x1, x2, &x2, x3, &x3, x4, &x4);
    return (x1+x2)*(x3-x4);
}

