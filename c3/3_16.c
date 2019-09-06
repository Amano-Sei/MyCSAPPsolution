/*************************************************************************
    > File Name: 3_16.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月02日 星期一 17时30分15秒
 ************************************************************************/

#include<stdio.h>

void cond(long a, long *p){
    if(!p)
        goto done;
    if(*p >= a)
        goto done;
    *p = a;
done:
    return;
}

