/*************************************************************************
    > File Name: 2_95.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 18时45分15秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "float_bits.h"
using namespace std;

float_bits float_half(float_bits f){
    unsigned exp = f>>23 & 0xff;
    if(exp < 2){
        return (f<<1>>2 | f&0x80000000)+((f&1)&&(f&2));
    }else if(exp < 255)
        return f-0x800000;
    else
        return f;
}

int main(){
    unsigned cur = 0, cans;
    float cf;
    int d = 0;
    do{
        cans = float_half(cur);
        cf = u2f(cur);
        //最开始的时候忘记了向偶数舍入，但很快发觉了，而且因为是乘0.5，舍入非常好做
        //起初忘记了默认浮点数是double，然后u2f出来的和0.5倍的不等，却具有一样的位模式...头疼了一会儿才发现是舍入的float和没舍入的double然后float强转double进行比较，自然会不等（（（
        if(isnan(cf) && cans!=cur || !isnan(cf) && 0.5f*cf!=u2f(cans))
            printf("warning... %x %x %x\n", cur, cans, getfb(cf*0.5f));
        cur++;
        if(cur % 0x10000000 == 0)
            printf("%d/16 done\n", ++d);
    }while(cur);
    printf("all done\n");
	return 0;
}

