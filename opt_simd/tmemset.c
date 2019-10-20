/*************************************************************************
    > File Name: memset.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月20日 星期日 11时57分56秒
 ************************************************************************/

#include <stdio.h>

#define VBYTES 32
//typedef unsigned char vec_t __attribute__ ((vector_size(VBYTES)));
typedef unsigned long long vec_t __attribute__ ((vector_size(VBYTES)));

void *memset(void *s, int c, size_t n){
    unsigned char *schar = s;
    if(n >= VBYTES*VBYTES){
        //尝试了两种写法，如果前向不跳的话对于少量的memset都避免不了预测惩罚
        while((unsigned long long)schar%VBYTES != 0)
            *schar++ = (unsigned char)c;
        vec_t cdata;
        unsigned long long ulc = (unsigned char)c;
        ulc = (((ulc << 56)|(ulc << 48))|((ulc << 40)|(ulc << 32)))|(((ulc << 24)|(ulc << 16))|((ulc << 8)|ulc));
        cdata[0] = ulc;
        cdata[1] = ulc;
        cdata[2] = ulc;
        cdata[3] = ulc;
        //cdata[0] = cdata[1] = cdata[2] = cdata[3] = 
        //cdata[4] = cdata[5] = cdata[6] = cdata[7] = 
        //cdata[8] = cdata[9] = cdata[10] = cdata[11] = 
        //cdata[12] = cdata[13] = cdata[14] = cdata[15] = 
        //cdata[16] = cdata[17] = cdata[18] = cdata[19] = 
        //cdata[20] = cdata[21] = cdata[22] = cdata[23] = 
        //cdata[24] = cdata[25] = cdata[26] = cdata[27] = 
        //cdata[28] = cdata[29] = cdata[30] = cdata[31] = 
        //    (unsigned char)c;
        //对着100多条的初始化语句懵逼...
        //然后改成上面这样了（
        
        //手调了下产出的汇编的赋值部分(三操作数四操作数让我着实花了好多时间去理解...
        //↑你都手调了，不调成少量的情况下没有惩罚（
        //emmm主要是不知道cpu到底会怎么预测，所以就不动这部分了（

        while(n >= VBYTES){
            *(vec_t *)schar = cdata;
            schar += VBYTES;
            n -= VBYTES;
        }
    }
    while(n > 0){
        *schar++ = (unsigned char)c;
        n--;
    }
    return s;
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

