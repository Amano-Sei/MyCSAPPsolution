/*************************************************************************
    > File Name: memset.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月20日 星期日 11时57分56秒
 ************************************************************************/

#include <stdio.h>

typedef unsigned long int op_t;
#define OPSIZ (sizeof(op_t))
#define VBYTES 32
#define VSIZE VBYTES/sizeof(op_t)
typedef op_t vec_t __attribute__ ((vector_size(VBYTES)));

void * __attribute__ ((__optimize__("-fno-tree-loop-distribute-patterns"))) memset(void *dstpp, int c, size_t len){
    unsigned char *dstp = dstpp;
    if(len >= VBYTES){
        size_t xlen;
        vec_t cdata;
        op_t ulc = (unsigned char)c;
        ulc |= ulc << 8;
        ulc |= ulc << 16;
        ulc |= ulc << 32;
        //期初这里不这样写是因为看到数据相关就难受...
        //for(int i = 0; i < VSIZE; i++)
        //    cdata[i] = ulc;
        //本来这里犹豫要改成这样，但是本来就是很特化的代码，所以还是默认是8字节long了
        cdata[0] = ulc;
        cdata[1] = ulc;
        cdata[2] = ulc;
        cdata[3] = ulc;
        //上面这里会在汇编里微调，我不知道c怎么写128位integer
        while((op_t)dstp % VBYTES != 0){
            *dstp++ = (unsigned char)c;
            len--;
        }

        xlen = len/(VBYTES*8);
        while(xlen){
            ((vec_t *)dstp)[0] = cdata;
            ((vec_t *)dstp)[1] = cdata;
            ((vec_t *)dstp)[2] = cdata;
            ((vec_t *)dstp)[3] = cdata;
            ((vec_t *)dstp)[4] = cdata;
            ((vec_t *)dstp)[5] = cdata;
            ((vec_t *)dstp)[6] = cdata;
            ((vec_t *)dstp)[7] = cdata;
            dstp += VBYTES*8;
            xlen--;
        }
        len %= VBYTES*8;
        xlen = len/VBYTES;
        while(xlen){
            ((vec_t *)dstp)[0] = cdata;
            dstp += VBYTES;
            xlen--;
        }
        len %= VBYTES;
        xlen = len/OPSIZ;
        while(xlen){
            ((op_t *)dstp)[0] = ulc;
            dstp += OPSIZ;
            xlen--;
        }
        len %= OPSIZ;
    }
    while(len){
        *dstp++ = (unsigned char)c;
        len--;
    }
    return dstpp;
}

char fort[3000];

int main(){
    for(int j = 1920; j < 1920+256; j++){
        for(int k = 0; k < VBYTES; k++){
            memset(&fort[k], (j-1920+k)%256, j);
            for(int i = 0; i < j; i++)
                if((unsigned char)fort[k+i] != (j-1920+k)%256)
                    printf("warning...with %d %d\n", i, fort[i]);
        }
    }
    printf("done...\n");
    return 0;
}

