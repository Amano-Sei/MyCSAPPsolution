/*************************************************************************
    > File Name: 2_72.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时37分09秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

void copy_int(int val, void *buf, int maxbytes){
    if(maxbytes >= sizeof(val))
        memcpy(buf, (void *)&val, sizeof(val));
}

int main(){
	return 0;
}

