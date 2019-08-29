/*************************************************************************
    > File Name: float_bits.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 14时06分28秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

typedef unsigned float_bits;

unsigned getfb(float f){
    return *(unsigned *)&f;
}

float u2f(unsigned x){
    return *(float *)(&x);
}

