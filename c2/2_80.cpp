/*************************************************************************
    > File Name: 2_80.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 14时57分35秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int threefourths(int x){
    int w = sizeof(int) << 3;
    return x-((((~(x>>(w-1)))&0xf)+x)>>2);
}

int main(){
	return 0;
}

