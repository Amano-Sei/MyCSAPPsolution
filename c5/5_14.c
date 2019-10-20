/*************************************************************************
    > File Name: 5_13.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月19日 星期六 23时10分55秒
 ************************************************************************/

#include <stdio.h>

#define DOUBLE

#include "vec.c"

void inner5(vec_ptr u, vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t)0;

    for(i = 0; i < length-5; i+=6){
        sum = sum + udata[i]*vdata[i];
        sum = sum + udata[i+1]*vdata[i+1];
        sum = sum + udata[i+2]*vdata[i+2];
        sum = sum + udata[i+3]*vdata[i+3];
        sum = sum + udata[i+4]*vdata[i+4];
        sum = sum + udata[i+5]*vdata[i+5];
    }

    while(i < length){
        sum = sum + udata[i]*vdata[i];
        i++;
    }

    *dest = sum;
}

