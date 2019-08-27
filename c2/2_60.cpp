/*************************************************************************
    > File Name: 2_60.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月27日 星期二 19时46分45秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

unsigned replace_byte(unsigned x, int i, unsigned char b){
    //unsigned char *bx = (unsigned char *)&x;
    //bx[i] = b;
    //return x;
    return (x&~(0xff << (i<<3)))|(b << (i<<3));
}

int main(){
    printf("%x %x\n", replace_byte(0x12345678, 2, 0xab), replace_byte(0x12345678, 0, 0xab));
	return 0;
}

