/*************************************************************************
    > File Name: 2_59.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月27日 星期二 19时43分01秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int getans(int x, int y){
    return (x&0xff)|(y&(~0xff));
}

int main(){
    printf("%x\n", getans(0x89abcdef, 0x76543210));
	return 0;
}

