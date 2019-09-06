/*************************************************************************
    > File Name: store_uprod.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月02日 星期一 10时10分11秒
 ************************************************************************/

#include <inttypes.h>

typedef unsigned __int128 uint128_t;

void store_uprod(uint128_t *dest, uint64_t x, uint64_t y){
    *dest = x*(uint128_t)y;
}

