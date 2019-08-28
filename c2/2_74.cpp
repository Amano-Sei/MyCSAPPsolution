/*************************************************************************
    > File Name: 2_74.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时59分32秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int tsub_ok(int x, int y){
    int intmin = 1 << (sizeof(int)<<3);
    int xt = intmin&x;
    int yt = intmin&y;
    int st = intmin&(x-y);
    return (xt^yt) && !(yt^st);
}

int main(){
	return 0;
}

