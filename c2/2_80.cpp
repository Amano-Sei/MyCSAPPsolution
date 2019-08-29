/*************************************************************************
    > File Name: 2_80.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 14时57分35秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int threefourths(int x){
    int w = sizeof(int) << 3;
    //不同于上一题，这道题不需要考虑溢出，似乎更简单？
    //基本思路就是求出一个向0相反方向舍入的1/4*x，再减去它就是向0方向舍入的3/4倍的x了
    //负数范围向下舍入，正数范围向上摄入，与有符号数除运算正好相反，做一轮相反的操作即可
    //看了其他dalao的做法，比我的更具有普适性
    return x-((((~(x>>(w-1)))&3)+x)>>2);
}

int main(){
    for(int i = -10; i < 11; i++)
        cout << i << "*(3/4) == " << threefourths(i) << endl;
	return 0;
}

