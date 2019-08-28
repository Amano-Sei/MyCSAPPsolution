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
    return ans;
}

int main(){
	return 0;
}

