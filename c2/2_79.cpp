/*************************************************************************
    > File Name: 2_79.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 11时37分12秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int mul3div4(int x){
    int w = sizeof(int)<<3;
    x = (x<<1)+x;
    //关于溢出到最后都不知道怎么处理，找了别人的答案也没有处理溢出...就这样吧（
    return (((x>>(w-1)) & 3)+x)>>2;
}

int main(){
	return 0;
}

