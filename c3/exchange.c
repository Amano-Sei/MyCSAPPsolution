/*************************************************************************
    > File Name: exchange.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月01日 星期日 15时21分57秒
 ************************************************************************/

#include<stdio.h>
long exchange(long *xp, long y){
    long x = *xp;
    *xp = y;
    return x;
}

