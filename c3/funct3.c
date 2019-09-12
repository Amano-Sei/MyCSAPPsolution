/*************************************************************************
    > File Name: funct3.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月09日 星期一 23时24分01秒
 ************************************************************************/

#include<stdio.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;

range_t fing_range(float x){
    int result;
    if(x < 0)
        result = NEG;
    else if(x == 0)
        result = ZERO;
    else if(x > 0)
        result = POS;
    else
        result = OTHER;
    return result;
}

