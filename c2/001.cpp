/*************************************************************************
    > File Name: 001.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年07月16日 星期二 17时32分27秒
 ************************************************************************/

#include <iostream>
#include <cmath>
using namespace std;

int main(){
    //double b = 1e20;
    //double a = 3.14;
    //cout << a+b-b << endl;
    //cout << a + (b-b) << endl;
    cout << (0xffffffff<0) << endl;
    cout << ((int)0xffffffff<0) << endl;
    for(int i = -5; i <= 10; i++)
        printf("%d===%.5x\n", i, i);
    cout << -10%3 << endl;
    cout << atan(-100/10)/M_PI*180;
    return 0;
}

