/*************************************************************************
    > File Name: 004.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年07月23日 星期二 00时17分45秒
 ************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cinttypes>
using namespace std;

int main(){
//    long long dd = 0x123456789abcdef << 64;
//    printf("%x\n", dd);
    int a = 1 << 31;
    printf("%d %u\n", a, abs(a));
    printf("%ld==%ld\n", INT64_MIN, INT64_MAX);
    printf("%s==%s\n", PRIu64, PRId64);
    printf("%d==%u\n", -1u, -1u);
    printf("%d==\n", -2147483648u);
}
