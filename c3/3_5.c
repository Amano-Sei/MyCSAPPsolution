/*************************************************************************
    > File Name: 3_5.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月01日 星期日 17时02分31秒
 ************************************************************************/

#include<stdio.h>

void decode1(long *xp, long *yp, long *zp){
    long x = *xp;
    long y = *yp;
    long z = *zp;
    *yp = x;
    *zp = y;
    *xp = z;
    //上面的更为接近
    //long y = *yp;
    //*yp = *xp;
    //*xp = *zp;
    //*zp = y;
}

