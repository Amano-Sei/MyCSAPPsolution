/*************************************************************************
    > File Name: 2_58.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月27日 星期二 19时39分55秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

bool is_little_endian(){
    int x = 0x1234;
    return ((unsigned char *)&x)[0] == 0x34;
}

int main(){
    printf("%d\n", is_little_endian());
	return 0;
}

