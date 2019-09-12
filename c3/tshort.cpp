/*************************************************************************
    > File Name: tshort.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月06日 星期五 18时23分06秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
struct d{
    int a;
    char b;
}aa;

int main(){
    cout << sizeof(short);
    cout << sizeof(d);
    cout << aa.a;
    aa = {1,2};
    cout << aa.a;
    aa = {4,3};
    cout << aa.a;
    cout << endl << sizeof(aa);
	return 0;
}

