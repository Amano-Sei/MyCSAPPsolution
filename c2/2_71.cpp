/*************************************************************************
    > File Name: 2_71.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时33分20秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum){
    return (int)(word << 8*(3-bytenum)) >> 24;
}

int main(){
    printf("%x", xbyte(0x81818181, 3));
	return 0;
}

