/*************************************************************************
    > File Name: 2_96.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 19时18分22秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "float_bits.h"
using namespace std;

int float_f2i(float_bits f){
    unsigned exp = f>>23 & 0xff;
    int e = exp-127;
    if(e >= 31)
        return 0x80000000;
    if(e < 0)
        return 0;
    int sign = ((int)f >> 31)|1;
    unsigned fac = f & 0x7fffff;
    fac += 0x800000;
    if(e <= 23)
        return (fac >> (23-e))*sign;
    return (fac << e-23)*sign;
}

int main(){
    unsigned cur = 0;
    int cans;
    float cf;
    int d = 0;
    do{
        cans = float_f2i(cur);
        cf = u2f(cur);
        if((int)cf != cans){
            printf("warning... cur = %x; cans = %x==%d; cf = %f; (int)cf = %x==%d\n", cur, cans, cans, cf, (int)cf, (int)cf);
            getchar();
        }
        cur++;
        if(cur % 0x10000000 == 0)
            printf("%d/16 done\n", ++d);
    }while(cur);
    printf("all done\n");
	return 0;
}

