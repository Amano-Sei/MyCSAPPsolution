/*************************************************************************
    > File Name: 5_13.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月19日 星期六 23时10分55秒
 ************************************************************************/

#include <stdio.h>

#define DOUBLE

#include "vec.c"

void inner7(vec_ptr u, vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);
    data_t sum = (data_t)0;

    for(i = 0; i < length-5; i+=6)
        sum = sum + ((udata[i]*vdata[i]+ udata[i+1]*vdata[i+1]) + (udata[i+2]*vdata[i+2] + udata[i+3]*vdata[i+3]) + (udata[i+4]*vdata[i+4]) + (udata[i+5]*vdata[i+5]));
    //看了dalao的代码直截了当只加了一个括号（，然而确实足够了

    while(i < length){
        sum = sum + udata[i]*vdata[i];
        i++;
    }

    *dest = sum;
}

