/*************************************************************************
    > File Name: 2_93.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 14时43分47秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "float_bits.h"
using namespace std;

float_bits float_absval(float_bits f){
    return f&(0x7fffffff + ((unsigned)((0x7f800000&f)==0x7f800000 && (0x7fffff&f)) << 31));
}

int main(){
    unsigned cur = 0, cans;
    float cf;
    int d = 0;
    do{
        cans = float_absval(cur);
        cf = u2f(cur);
        if(isnan(cf) && cans!=cur || !isnan(cf) && abs(cf)!=u2f(cans))
            printf("warning... %x %x %f %f\n", cur, cans, cf, abs(cf));
        cur++;
        if(cur % 0x10000000 == 0)
            printf("%d/16 done\n", ++d);
    }while(cur);
    printf("all done\n");
	return 0;
}

