/*************************************************************************
    > File Name: 2_66.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时20分48秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int leftmost_one(unsigned x){
    x |= x>>1;
    x |= x>>2;
    x |= x>>4;
    x |= x>>8;
    x |= x>>16;
    return (x>>1)+1;
}

int main(){
    cout << leftmost_one(17);
	return 0;
}

