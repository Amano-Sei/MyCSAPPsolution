/*************************************************************************
    > File Name: 5_13.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月19日 星期六 23时10分55秒
 ************************************************************************/

#include <stdio.h>

#define DOUBLE

#include "vec.c"

void inner6(vec_ptr u, vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum0 = (data_t)0;
    data_t sum1 = (data_t)0;
    data_t sum2 = (data_t)0;
    data_t sum3 = (data_t)0;
    data_t sum4 = (data_t)0;
    data_t sum5 = (data_t)0;

    for(i = 0; i < length-5; i+=6){
        sum0 = sum0 + udata[i]*vdata[i];
        sum1 = sum1 + udata[i+1]*vdata[i+1];
        sum2 = sum2 + udata[i+2]*vdata[i+2];
        sum3 = sum3 + udata[i+3]*vdata[i+3];
        sum4 = sum4 + udata[i+4]*vdata[i+4];
        sum5 = sum5 + udata[i+5]*vdata[i+5];
    }

    while(i < length){
        sum0 = sum0 + udata[i]*vdata[i];
        i++;
    }

    *dest = (sum0+sum1)+(sum2+sum3)+(sum4+sum5);
}

