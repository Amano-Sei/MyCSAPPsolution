/*************************************************************************
    > File Name: 2_69.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时28分15秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

unsigned rotate_left(unsigned x, int n){
    int w = sizeof(int) << 3;
    return (x>>(w-n-1)>>1) | (x << n);
}

int main(){
    printf("%x", rotate_left(0x12345678, 20));
	return 0;
}

