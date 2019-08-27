/*************************************************************************
    > File Name: 2_65.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月27日 星期二 20时50分18秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int odd_ones(unsigned x){
    x ^= x>>1;
    x ^= x>>2;
    x ^= x>>4;
    x ^= x>>8;
    x ^= x>>16;
    return x&1;
}

int main(){
	return 0;
}

