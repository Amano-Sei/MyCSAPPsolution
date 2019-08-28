/*************************************************************************
    > File Name: 2_70.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时30分13秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int fit_bits(int x, int n){
    int cx = x>>(n-1);
    return !(~cx) || !cx;
}

int main(){
    cout << fit_bits(-3, 2);
	return 0;
}

