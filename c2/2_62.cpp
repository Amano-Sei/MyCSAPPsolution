/*************************************************************************
    > File Name: 2_62.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月27日 星期二 20时18分37秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

bool int_shifts_are_arithmetic(){
    int x = -1;
    int w = sizeof(int) << 3;
    return (x>>(w-1)) & 0x2;
}

int main(){
	return 0;
}

