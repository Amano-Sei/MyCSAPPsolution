/*************************************************************************
    > File Name: 2_67.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时22分45秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int bad_int_size_is_32(){
    //int set_msb = 1 << 31;
    //int beyond_msb = (1 << 16) << 16;
    //return set_msb && !beyong_msb;
    int set_msb = 1 << 15 << 15;
    return (set_msb<<1) && !(set_msb<<2);
}

int main(){
	return 0;
}

