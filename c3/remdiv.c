/*************************************************************************
    > File Name: remdiv.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月02日 星期一 10时25分05秒
 ************************************************************************/

#include<stdio.h>

void remdiv(long x, long y, long *qp, long *rp){
    long q = x/y;
    long r = x%y;
    *qp = q;
    *rp = r;
}

