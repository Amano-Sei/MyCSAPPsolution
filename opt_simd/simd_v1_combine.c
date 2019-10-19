/*************************************************************************
    > File Name: simd_v1_combine.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月19日 星期六 19时20分21秒
 ************************************************************************/

#include <stdio.h>

#define INT
#define PROD

#include "vec.c"

#define VBYTES 32
#define VSIZE VBYTES/sizeof(data_t)
typedef data_t vec_t __attribute__ ((vector_size(VBYTES)));

void simd_v1_combine(vec_ptr v, data_t *dest){
    long i;
    vec_t accum;
    data_t *data = get_vec_start(v);
    int cnt = vec_length(v);
    data_t result = IDENT;

    for(i = 0; i < VSIZE; i++)
        accum[i] = IDENT;
    
    while(( (size_t)data % VBYTES) != 0 && cnt){
        result = result OP *data++;
        cnt--;
    }
    while(cnt >= VSIZE){
        vec_t chunk = *((vec_t *) data);
        accum = accum OP chunk;
        data += VSIZE;
        cnt -= VSIZE;
    }
    while(cnt){
        result = result OP *data++;
        cnt--;
    }
    for(i = 0; i < VSIZE; i++)
        result = result OP accum[i];
    *dest = result;
}

