/*************************************************************************
    > File Name: 2_63.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月27日 星期二 20时27分33秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

unsigned srl(unsigned x, int k){
    unsigned xsra = (int) x >> k;
    return xsra & ((1<<sizeof(int)*8-k)-1);
}

int sra(int x, int k){
    int xsrl = (unsigned) x >> k;
    int w = sizeof(int)*8;
    return xsrl | ~(((xsrl & (1<<w-k-1))<<1)-1);
}

int main(){
    printf("%x\n", sra(0x12345678, 4));
	return 0;
}

