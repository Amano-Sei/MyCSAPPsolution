/*************************************************************************
    > File Name: 2_97.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 20时06分51秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "float_bits.h"
using namespace std;

//在室友的睡眠时间之间挤出来的编程时间
//终于来到了最后一题！
//还差一个lab我就可以进入第三章了

float_bits float_i2f(int i){
    if(!i)
        return 0;
    int sign = i>>31;
    unsigned ui = i*(sign|1), tmp = ui, tt;
    int e = 0, ct = 16;
    while(ct){
        //这里有个小插曲，一开始写完跑的很慢，推测主要性能损耗在计算位数这里
        //写了个log32的算法，结果莫名其妙跑不出来结果
        //仔细一看自己写了个死循环噗...
        tt = tmp >> ct;
        if(tt){
            tmp = tt;
            e += ct;
        }
        ct >>= 1;
    }
    unsigned fsign = sign&1, exp = e+127, frac;
    if(e > 23){
        frac = ui>>e-23 & 0x7fffff;
        if(e > 23){
            unsigned thr = ((1<<e-23)-1) & ui;
            if(thr == 1<<e-24 && (frac&1) || thr > 1 << e-24){
                frac += 1;
                if(frac == 0x800000){
                    frac = 0;
                    exp++;
                }
            }
        }
    }else
        frac = ui<<23-e & 0x7fffff;
    return (fsign<<31) | (exp<<23) | frac;
}

int main(){
    unsigned cur = 0, cans;
    float cansf, cf;
    int d = 0;
    do{
        cans = float_i2f(cur);
        cansf = u2f(cans);
        cf = (float)((int)cur);
        if(cf != cansf){
            printf("warning... cur = %x; cans = %x; cansf = %f; cf = %f, getfb(cf) = %x\n", cur, cans, cansf, cf, getfb(cf));
            getchar();
        }
        cur++;
        if(cur % 0x10000000 == 0)
            printf("%d/16 done\n", ++d);
    }while(cur);
    printf("all done\n");
	return 0;
}

