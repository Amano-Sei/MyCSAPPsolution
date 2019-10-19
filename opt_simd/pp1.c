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

void simd_v2_combine(vec_ptr v, data_t *dest){
    long i;
    vec_t accum0, accum1, accum2, accum3;
#if defined(INT)||defined(FLOAT)
    vec_t accum4, accum5, accum6, accum7;
#endif
    data_t *data = get_vec_start(v);
    int cnt = vec_length(v);
    data_t result = IDENT;

    for(i = 0; i < VSIZE; i++){
        accum0[i] = accum1[i] = accum2[i] = accum3[i] = IDENT;
#if defined(INT)||defined(FLOAT)
        accum4[i] = accum5[i] = accum6[i] = accum7[i] = IDENT;
#endif
    }
    
    while(( (size_t)data % VBYTES) != 0 && cnt){
        result = result OP *data++;
        cnt--;
    }
    while(cnt >= VSIZE*VSIZE){
        vec_t chunk0 = *((vec_t *)data);
        accum0 = accum0 OP chunk0;
        vec_t chunk1 = *((vec_t *)(data+VSIZE));
        accum1 = accum1 OP chunk1;
        vec_t chunk2 = *((vec_t *)(data+2*VSIZE));
        accum2 = accum2 OP chunk2;
        vec_t chunk3 = *((vec_t *)(data+3*VSIZE));
        accum3 = accum3 OP chunk3;
#if defined(INT)||defined(FLOAT)
        vec_t chunk4 = *((vec_t *)(data+4*VSIZE));
        accum4 = accum4 OP chunk4;
        vec_t chunk5 = *((vec_t *)(data+5*VSIZE));
        accum5 = accum5 OP chunk5;
        vec_t chunk6 = *((vec_t *)(data+6*VSIZE));
        accum6 = accum6 OP chunk6;
        vec_t chunk7 = *((vec_t *)(data+7*VSIZE));
        accum7 = accum7 OP chunk7;
#endif
        data += VSIZE*VSIZE;
        cnt -= VSIZE*VSIZE;
    }
    while(cnt >= VSIZE){
        vec_t chunk0 = *((vec_t *)data);
        accum0 = accum0 OP chunk0;
        data += VSIZE;
        cnt -= VSIZE;
    }
    //实际想想，vsize为4时最多才15个
    while(cnt){
        result = result OP *data++;
        cnt--;
    }
    accum0 = ((accum0 OP accum1) OP (accum2 OP accum3))
#if defined(INT)||defined(FLOAT)
        OP ((accum4 OP accum5) OP (accum6 OP accum7))
#endif
    ;
    //emmm感觉这个结合优化应该是编译器可以做的（
    for(i = 0; i < VSIZE; i++)
        result = result OP accum0[i];
    *dest = result;
}

