/*************************************************************************
    > File Name: pp4.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月21日 星期一 13时56分12秒
 ************************************************************************/

#include <stdio.h>

#define DOUBLE

#include "vec.c"

#define VBYTES 32
#define VSIZE VBYTES/sizeof(data_t)
typedef data_t vec_t __attribute__((vector_size(VBYTES)));

data_t inner9(vec_ptr u, vec_ptr v, data_t *dest){
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
    vec_t vsum1 = {0};
    vec_t vsum2 = {0};
    vec_t vsum3 = {0};
    while(length >= 4*VSIZE){
        vec_t uchunk = *(vec_t *)udata;
        vec_t vchunk = *(vec_t *)vdata;
        vsum = vsum + uchunk*vchunk;

        uchunk = *(vec_t *)(udata+VSIZE);
        vchunk = *(vec_t *)(vdata+VSIZE);
        vsum1 = vsum1 + uchunk*vchunk;

        uchunk = *(vec_t *)(udata+2*VSIZE);
        vchunk = *(vec_t *)(vdata+2*VSIZE);
        vsum2 = vsum2 + uchunk*vchunk;

        uchunk = *(vec_t *)(udata+3*VSIZE);
        vchunk = *(vec_t *)(vdata+3*VSIZE);
        vsum3 = vsum3 + uchunk*vchunk;

        udata += 4*VSIZE;
        vdata += 4*VSIZE;
        length -= 4*VSIZE;
    }
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

