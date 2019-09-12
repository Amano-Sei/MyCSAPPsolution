/*************************************************************************
    > File Name: 3_59.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 14时14分30秒
 ************************************************************************/

#include <stdio.h>
#include <stdint.h>

typedef __int128 int128_t;
void store_prod(int128_t *dest, int64_t x, int64_t y){
    *dest = x * (int128_t)y;
}

