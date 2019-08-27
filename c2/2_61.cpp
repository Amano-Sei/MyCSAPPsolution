/*************************************************************************
    > File Name: 2_61.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月27日 星期二 20时01分46秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

bool getans(int x){
    int sv = ;
    return !(~x) || !x || !(x&0xff^0xff) || !((unsigned)x>>((sizeof(int)-1)<<3));
}

int main(){
	return 0;
}

