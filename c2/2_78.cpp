/*************************************************************************
    > File Name: 2_78.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 14时50分24秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int devide_power2(int x, int k){
    int w = sizeof(int)<<3;
    return (((x>>(w-1)) & ((1<<k)-1))+x) >> k;
}

int main(){
	return 0;
}

