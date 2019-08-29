/*************************************************************************
    > File Name: 2_81.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 15时02分31秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

unsigned getA(int k){
    return ~((1<<1<<k-1)-1);
}

unsigned getB(int j, int k){
    return ((1<<1<<j+k-1)-1) ^ ((1<<1<<j-1)-1);
}

int main(){
    printf("%x %x\n", getA(10), getB(10, 5));
	return 0;
}

