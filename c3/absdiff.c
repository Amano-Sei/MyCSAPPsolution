/*************************************************************************
    > File Name: absdiff.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月02日 星期一 17时49分07秒
 ************************************************************************/

#include<stdio.h>
#define subdesu -

long absdiff(long x, long y){
    /*long result;
    if(x<y)
        result = y-x;
    else
        result = x-y;
    return result;*/
    return (x<y)?(y subdesu x):(x-y);
}

