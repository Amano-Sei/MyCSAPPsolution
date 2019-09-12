/*************************************************************************
    > File Name: 3_62.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 18时07分08秒
 ************************************************************************/

#include<stdio.h>

typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;

long switch3(long *p1, long *p2, mode_t action){
    long result = 0;
    switch(action){
        case MODE_A:
            result = *p2;
            *p2 = *p1;
            break;
        case MODE_B:
            result = *p1+*p2;
            *p1 = result;
            break;
        case MODE_C:
            *p1 = 59;
            result = *p2;
            break;
        case MODE_D:
            *p1 = *p2;
            //注意题意中有提到存在落入其他情况的情况
        case MODE_E:
            result = 27;
            break;
        default:
            result = 12;
    }
    return result;
}

