/*************************************************************************
    > File Name: 2_73.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时49分51秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int saturating_add(int x, int y){
    //int sum = x+y;
    //int intmin = 1 << (sizeof(int) << 3);
    //!(x&intmin)&&!(y&intmin)&&(sum&intmin)&&(sum=intmin-1);
    //(x&intmin)&&(y&intmin)&&!(sum&intmin)&&(sum=intmin);
    //上面是cheat的说...本质上还是条件判断了
    //return sum;
    
    int z = x+y;
    int sum = z;
    int w = sizeof(int) << 3;
    x >>= w-1;
    y >>= w-1;
    z >>= w-1;
    int base = (x^z)&(y^z);
    return (sum|base)-(1&~x&~y&z)-((unsigned)base>>1);
    //一开始参考了大佬的写出了base，经过思考写出自己最终式真的很开心，再看dalao的逻辑虽然是一样的，但是在自闭的时候写出来真的真的很开心...
}

int main(){
    printf("%x\n", saturating_add(0x40000000, 0x40000000));
    printf("%x", saturating_add(0x80000000, 0x80000000));
	return 0;
}

