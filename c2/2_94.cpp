/*************************************************************************
    > File Name: 2_94.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 15时05分41秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
#include "float_bits.h"
using namespace std;

//突然发觉网上找到的题解都用了if...自己也死活想不到不需要判断只用位运算的做法
//再看前面的要求，“位级整数编码规则”，行吧，有if不仅是这道，包括前面的都是脚写诶QAQ
/*
float_bits float_twice(float_bits f){
    float_bits ans = 0;
    float_bits ft = f&0x80000000;
    float_bits fe = f&0x7f800000;
    float_bits fm = f&0x7fffff;
    fe==0 && (ans=(fm<<1)|ft) && 0 ||
    fe&& ((fe-0x7f700000)&0x80000000) && (ans=f+0x800000) ||
    fe==0x7f700000 && (ans=fe|ft) ||
    fe==0x7f800000 && (ans = f) ||
    return ans;
}*/

float_bits float_twice(float_bits f){
    unsigned sign = f>>31;
    unsigned exp = f>>23 & 0xff;
    unsigned fac = f & 0x7fffff;
    /*if(exp == 0)
        fac <<= 1;
    //溢出的情况下会因为位或运算导致结果还是正确的
    else if(exp < 0xfe)
        exp += 1;
    else if(exp == 0xfe){
        exp += 1;
        fac = 0;
    }*/
    fac <<= !exp;
    unsigned t = ~exp+0xff;
    fac = fac & (~!!t +1);
    exp = exp + (!!exp & (t>>31 & 1 ^ 1));
    return sign<<31 | exp<<23 | fac;
}
//在写datalab的时候重看了这里，感觉只用位运算不是不可能...
//事实证明是可以的

int main(){
    //本来想写个测试函数的，但是不知道怎么传判断错误的表达式
    
    unsigned cur = 0, cans;
    float cf;
    int d = 0;
    do{
        cans = float_twice(cur);
        cf = u2f(cur);
        if(isnan(cf) && cans!=cur || !isnan(cf) && 2*cf!=u2f(cans)){
            printf("warning... %x %x %f\n", cur, cans, cf);
            getchar();
        }
        cur++;
        if(cur % 0x10000000 == 0)
            printf("%d/16 done\n", ++d);
    }while(cur);
    printf("all done\n");

	return 0;
}

