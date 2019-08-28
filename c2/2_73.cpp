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
    int sum = x+y;
    int intmin = 1 << (sizeof(int) << 3);
    !(x&intmin)&&!(y&intmin)&&(sum&intmin)&&(sum=intmin-1);
    (x&intmin)&&(y&intmin)&&!(sum&intmin)&&(sum=intmin);
    return sum;
}

int main(){
	return 0;
}

