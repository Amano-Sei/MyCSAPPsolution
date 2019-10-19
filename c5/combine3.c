/*************************************************************************
    > File Name: combine3.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月15日 星期二 20时05分01秒
 ************************************************************************/

#include <stdio.h>

//#define INT
#define DOUBLE
#define PROD

#include "combine.h"

void combine3(vec_ptr v, data_t *dest){
    long i;
    long length = vec_length(v);
    data_t *data = get_vec_start(v);

    *dest = IDENT;
    for(i = 0; i < length; i++)
        *dest = *dest OP data[i];
}

