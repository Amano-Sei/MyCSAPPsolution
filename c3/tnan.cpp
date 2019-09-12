/*************************************************************************
    > File Name: tnan.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月09日 星期一 22时43分25秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

int main(){
    double a = sqrt(-.01);
    cout << a << endl;
    cout << (a > 1.0) << (a < 1.0) << (a == 1.0) << endl;
	return 0;
}

