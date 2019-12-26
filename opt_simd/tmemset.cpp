/*************************************************************************
    > File Name: memset.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月20日 星期日 11时57分56秒
 ************************************************************************/

#include <stdio.h>

#define VBYTES 32

void * __attribute__ ((__optimize__("-fno-tree-loop-distribute-patterns"))) mymemset(void *dstpp, int c, size_t len);
char fort[3000];

int main(){
    for(int j = 1920; j < 1920+256; j++){
        for(int k = 0; k < VBYTES; k++){
            mymemset(&fort[k], (j-1920+k)%256, j);
            for(int i = 0; i < j; i++)
                if((unsigned char)fort[k+i] != (j-1920+k)%256)
                    printf("warning...with %d %d\n", i, fort[i]);
        }
    }
    printf("done...\n");
    return 0;
}

