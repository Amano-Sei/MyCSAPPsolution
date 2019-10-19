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

void simd_v3_combine(vec_ptr v, data_t *dest){
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
    while(cnt >= VSIZE*VSIZE){
        vec_t chunk0 = *((vec_t *)data);
        vec_t chunk1 = *((vec_t *)(data+VSIZE));
        vec_t chunk2 = *((vec_t *)(data+2*VSIZE));
        vec_t chunk3 = *((vec_t *)(data+3*VSIZE));
#if defined(INT)||defined(FLOAT)
        vec_t chunk4 = *((vec_t *)(data+4*VSIZE));
        vec_t chunk5 = *((vec_t *)(data+5*VSIZE));
        vec_t chunk6 = *((vec_t *)(data+6*VSIZE));
        vec_t chunk7 = *((vec_t *)(data+7*VSIZE));
#endif
        accum = accum OP (((chunk0 OP chunk1) OP (chunk2 OP chunk3))
#if defined(INT)||defined(FLOAT)
                OP ((chunk4 OP chunk5) OP (chunk6 OP chunk7))
#endif
                );
        data += VSIZE*VSIZE;
        cnt -= VSIZE*VSIZE;
    }
    while(cnt >= VSIZE){
        vec_t chunk = *((vec_t *)data);
        accum = accum OP chunk;
        data += VSIZE;
        cnt -= VSIZE;
    }
    //实际想想，vsize为4时最多才15个
    while(cnt){
        result = result OP *data++;
        cnt--;
    }
    ;
    //emmm感觉这个结合优化应该是编译器可以做的（
    for(i = 0; i < VSIZE; i++)
        result = result OP accum[i];
    *dest = result;
}

