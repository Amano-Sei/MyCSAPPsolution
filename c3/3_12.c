/*************************************************************************
    > File Name: 3_12.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月02日 星期一 10时33分10秒
 ************************************************************************/

#include<stdio.h>

void uremdiv(unsigned long x, unsigned long y, unsigned long *qp, unsigned long *rp){
    unsigned long q = x/y;
    unsigned long r = x%y;
    *qp = q;
    *rp = r;
}

