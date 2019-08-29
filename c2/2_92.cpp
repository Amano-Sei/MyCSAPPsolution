/*************************************************************************
    > File Name: 2_92.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 14时04分49秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "float_bits.h"
using namespace std;

float_bits float_negate(float_bits f){
    float_bits op = (f&0x7f800000)!=0x7f800000 || !(f&0x7fffff);
    op <<= 31;
    return op^f;
}

int main(){
    unsigned cur = 0, cans;
    float cf;
    int d = 0;
    do{
        cf = u2f(cur);
        cans = float_negate(cur);
        if(!isnan(cf) && -u2f(cur) != u2f(cans) || isnan(cf) && cur!=cans)
            printf("%x %f\n", cur, u2f(cur));
        cur++;
        if(cur % 0x10000000 == 0)
            printf("%d/16 done\n", ++d);
    }while(cur);
    printf("all done\n");
	return 0;
}

