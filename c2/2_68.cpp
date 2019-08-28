/*************************************************************************
    > File Name: 2_68.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 13时25分11秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int lower_one_mask(int n){
    return (1 << n-1 << 1)-1;
}

int main(){
    cout << lower_one_mask(31);
	return 0;
}

