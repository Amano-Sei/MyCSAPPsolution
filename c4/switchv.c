/*************************************************************************
    > File Name: switchv.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月02日 星期三 10时37分10秒
 ************************************************************************/

#include <stdio.h>

long switchv(long idx){
    long result = 0;
    switch(idx){
        case 0:
            result = 0xaaa;
            break;
        case 2:
        case 5:
            result = 0xbbb;
            break;
        case 3:
            result = 0xccc;
        default:
            result = 0xddd;
    }
    return result;
}

#define CNT 8
#define MINVAL -1

int main(){
    long vals[CNT];
    long i;
    for(i = 0; i < CNT; i++){
        vals[i] = switchv(i+MINVAL);
        printf("idx = %ld, val = 0x%lx\n", i+MINVAL, vals[i]);
    }
    return 0;
}

