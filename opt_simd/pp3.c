/*************************************************************************
    > File Name: pp3.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月21日 星期一 10时48分12秒
 ************************************************************************/

#include <stdio.h>

#define DOUBLE

#include "vec.c"

#define VBYTES 32
#define VSIZE VBYTES/sizeof(data_t)
typedef data_t vec_t __attribute__((vector_size(VBYTES)));

data_t inner8(vec_ptr u, vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(u);
    data_t *udata = get_vec_start(u);
    data_t *vdata = get_vec_start(v);

    data_t sum = (data_t)0;
    while((long)udata % VBYTES != 0 && length > 0){
        sum = sum+ *udata++ * *vdata++;
        length--;
    }
    //vec_t vsum;
    //for(int i = 0; i < VSIZE; i++)
    //    vsum[i] = 0;
    vec_t vsum = {0};
    while(length >= VSIZE){
        vsum = vsum + *(vec_t *)udata * *(vec_t *)vdata;
        udata += VSIZE;
        vdata += VSIZE;
        length -= VSIZE;
    }
    while(length > 0){
        sum = sum + *udata++ * *vdata++;
        length--;
    }
    for(int i = 0; i < VSIZE; i++)
        sum = sum + vsum[i];
    return sum;
}

