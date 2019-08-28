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
    return (long long)x * y >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y){
    int w = sizeof(int)<<3;
    return (x >> w-1)*x + (y >> w-1)*y + signed_high_prod(x, y);
}

int main(){
	return 0;
}

