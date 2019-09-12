/*************************************************************************
    > File Name: checktocal.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月07日 星期六 21时46分48秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main(){
    freopen("./tlocaldesu", "r", stdin);
    unsigned long long cmax = 0x0, cmin = 0xffffffffffffffff, cur;
    while(scanf("%llx", &cur) != EOF){
        cmax = max(cmax, cur);
        cmin = min(cmin, cur);
    }
    printf("local min at %llx\n", cmin);
    printf("local max at %llx\n", cmax);
    printf("%llx==%lld\n", cmax-cmin, cmax-cmin);
	return 0;
}

