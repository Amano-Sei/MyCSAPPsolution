/*************************************************************************
    > File Name: 2_76.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月28日 星期三 14时36分42秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

void *calloc(size_t nmemb, size_t size){
    void *ans = NULL;
    size_t bufsize = nmemb*size;
    bufsize && bufsize/nmemb == size && ans = malloc(bufsize) && memset(ans, 0, bufsize);
    //到最后也没明白怎么不用乘除来做...还用上了前面的作弊
    //先就这样吧...
    return ans;
}

int main(){
	return 0;
}

