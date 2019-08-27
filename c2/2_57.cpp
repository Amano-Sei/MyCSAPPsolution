/*************************************************************************
    > File Name: 2_57.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月27日 星期二 19时35分37秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len){
    for(size_t i = 0; i < len; i++)
        printf(" %.2x", start[i]);
    printf("\n");
}

void show_short(short x){
    show_bytes((byte_pointer)&x, sizeof(short));
}

void show_long(long x){
    show_bytes((byte_pointer)&x, sizeof(long));
}

void show_double(double x){
    show_bytes((byte_pointer)&x, sizeof(double));
}

int main(){
	return 0;
}

