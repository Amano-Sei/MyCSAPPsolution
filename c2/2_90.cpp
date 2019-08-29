/*************************************************************************
    > File Name: 2_90.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 13时27分23秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

float u2f(unsigned x){
    return *(float *)&x;
}

float fpwr2(int x){
    unsigned exp, frac;
    unsigned u;
    if(x < -149){
        exp = 0;
        frac = 0;
    }else if(x < -126){
        exp = 0;
        frac = 1 << x+149;
    }else if(x < 128){
        exp = x + 127;
        frac = 0;
    }else{
        esp = 255;
        frac = 0;
    }

    u = exp << 23 | frac;
    return u2f(u);
}

int main(){
	return 0;
}

