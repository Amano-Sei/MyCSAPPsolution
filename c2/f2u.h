/*************************************************************************
    > File Name: f2u.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年08月29日 星期四 12时13分29秒
 ************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

bool is_little_endian(){
    int x = 0x1234;
    return ((unsigned char *)(&x))[0] == 0x34;
}

/*unsigned f2u(float x){
    unsigned ans = 0;
    unsigned char *pc = (unsigned char *)&x;
    if(is_little_endian())
        for(size_t i = 0; i < 4; i++)
            ans |= (unsigned)pc[i] << i*8;
    else
        for(size_t i = 0; i < 4; i++)
            ans |= (unsigned)pc[i] << 24-i*8;
    return ans;
}*/
unsigned f2u(float x){
    return *(unsigned *)&x;
    //呜呜呜...居然没想到指针QAQ
}

