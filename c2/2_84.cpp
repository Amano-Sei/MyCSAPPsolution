/*************************************************************************
    > File Name: 2_84.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 12时12分59秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include "f2u.h"
using namespace std;

int float_le(float x, float y){
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return sx && !sy && (ux|uy)!=1<<31 ||
            !(sx^sy) && ((ux-uy)>>31)^sx;
    //这个时候才意识到不用大于号小于号还可以用符号位来判断大小
    //位或运算符居然优先级比!=低的...
}

int main(){
    printf("%x\n", f2u(1));
    cout << float_le(+0.0, -0.0) << endl;
    cout << float_le(0.1, 0.2) << endl;
    cout << float_le(0.2, 0.1) << endl;
    cout << float_le(-0.1, -0.2) << endl;
    cout << float_le(-0.2, -0.1) << endl;
    long double a = 0;
    ((unsigned char *)&a)[0] = 1;
    cout << a << endl;
    double c = 0.0;
    c /= c;
    cout << (c==(1/1));
	return 0;
}

