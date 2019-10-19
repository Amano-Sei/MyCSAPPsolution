/*************************************************************************
    > File Name: combine1.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月14日 星期一 20时31分08秒
 ************************************************************************/

#include <stdio.h>

#define LONG
#define PROD

#include "combine.h"

//void combine1(long *p, int len, long *dest){
//    long i;
//    *dest = 0;
//    for(i = 0; i < len; i++)
//        *dest = *dest + p[i];
//}


void combine1(vec_ptr v, data_t *dest){
    long i;
    *dest = IDENT;
    for(i = 0; i < vec_length(v); i++){
        data_t val;
        get_vec_element(v, i, &val);
        *dest = *dest OP val;
    }
}

