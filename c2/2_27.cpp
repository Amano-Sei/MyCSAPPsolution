/*************************************************************************
    > File Name: 2_27.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月25日 星期日 20时22分38秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int uadd_ok(unsigned x, unsigned y){
    return x <= x+y;
}

int tadd_ok(int x, int y){
    return (x+y<0||x>=0||y>=0) && (x+y>0||x<=0||y<=0);
}

int tsub_ok(int x, int y){
    return !(x>0&&y<0&&x-y<0 && x<0&&y>0&&x-y>0);
}

int main(){
    printf("%d\n", INT32_MIN-INT32_MAX);
	return 0;
}

