/*************************************************************************
    > File Name: tvec.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月19日 星期六 18时10分06秒
 ************************************************************************/

#include <stdio.h>

typedef int data_t;
#define IDENT 0
#define VBYTES 32
#define VSIZE VBYTES/sizeof(data_t)
typedef data_t vec_t __attribute__ ((vector_size(VBYTES)));

//貌似最新的avx-512有32个512位的zmm寄存器...
//貌似我的cpu是不支持这个指令集的（
//看了眼i9非移动版是支持这个的！果然有钱真好啊...

data_t innerv(vec_t av, vec_t bv){
    long int i;
    vec_t pv = av*bv;
    data_t result = 0;
    for(i = 0; i < VSIZE; i++)
        result += pv[i];
    return result;
}

//5.17让我想起来了之前看过dalao说的优化memset...当初是看不懂说的是什么的（
//现在想起来了的话，那么实现一个32字节一挪的memset不是很棒么...

void tmov(vec_t *p){
    vec_t a = {1,1,1,1};
    *p = a;
}

