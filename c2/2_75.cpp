/*************************************************************************
    > File Name: 2_75.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 14时05分49秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int signed_high_prod(int x, int y){
    //验证的时候才意识到自己踩坑了，直接转可能会改变符号...
    long long lx = (long long)x << 32 >> 32, ly = (long long)y << 32 >> 32;
    return lx*ly >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y){
    int w = sizeof(int)<<3;
    return signed_high_prod(x, y) + (x >> w-1)*(x<<1>>1) + (y >> w-1)*(y<<1>>1);
}

unsigned long long nopans(unsigned x, unsigned y){
    return (unsigned long long)x * y >> 32;
}

int main(){
    printf("%x==%x\n", unsigned_high_prod(0xf0000000, 0x70000000), nopans(0xf0000000, 0x70000000));
	return 0;
}

