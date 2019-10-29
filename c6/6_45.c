/*************************************************************************
    > File Name: 6_45.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月26日 星期六 18时18分44秒
 ************************************************************************/

#include <stdio.h>

//把读和写分开进行，确保在缓存块大小合理的情况下四个读最少能有一个读能享受到缓存，不过更多的情况下平均会有三个甚至更多读缓存命中(要看块大小
//这个不知道算不算16*4展开，感觉更像是16*1...不过唯一的数据依赖链是读出写入，所以是16*16?emmm不知道这个*后面是怎么定义的（
//运气好的话，写应该也能享受到缓存
//本来想调一下算地址的地方，但是算了一下变量数寄存器有点紧张（算了
//在最坏情况下（首地址不对齐缓存块大小，且缓存块大小是8B）也最少能保证4个读里有1个缓存命中
//不过没有检测程序或者各种参数，总有种如果有测试程序跑一下就自闭的感觉（architecture lab的阴影...

void transpose(int *dst, int *src, int dim){
    int i, j;
    for(i = 0; i < dim-3; i+=4){
        for(j = 0; j < dim-3; j+=4){
            int t1 = src[i*dim+j];
            int t2 = src[i*dim+j+1];
            int t3 = src[i*dim+j+2];
            int t4 = src[i*dim+j+3];
            dst[j*dim+i] = t1;
            dst[(j+1)*dim+i] = t2;
            dst[(j+2)*dim+i] = t3;
            dst[(j+3)*dim+i] = t4;

            t1 = src[(i+1)*dim+j];
            t2 = src[(i+1)*dim+j+1];
            t3 = src[(i+1)*dim+j+2];
            t4 = src[(i+1)*dim+j+3];
            dst[j*dim+i+1] = t1;
            dst[(j+1)*dim+i+1] = t2;
            dst[(j+2)*dim+i+1] = t3;
            dst[(j+3)*dim+i+1] = t4;

            t1 = src[(i+2)*dim+j];
            t2 = src[(i+2)*dim+j+1];
            t3 = src[(i+2)*dim+j+2];
            t4 = src[(i+2)*dim+j+3];
            dst[j*dim+i+2] = t1;
            dst[(j+1)*dim+i+2] = t2;
            dst[(j+2)*dim+i+2] = t3;
            dst[(j+3)*dim+i+2] = t4;

            t1 = src[(i+3)*dim+j];
            t2 = src[(i+3)*dim+j+1];
            t3 = src[(i+3)*dim+j+2];
            t4 = src[(i+3)*dim+j+3];
            dst[j*dim+i+3] = t1;
            dst[(j+1)*dim+i+3] = t2;
            dst[(j+2)*dim+i+3] = t3;
            dst[(j+3)*dim+i+3] = t4;
        }
        while(j < dim){
            int t1 = src[i*dim+j];
            int t2 = src[(i+1)*dim+j];
            int t3 = src[(i+2)*dim+j];
            int t4 = src[(i+3)*dim+j];
            dst[j*dim+i] = t1;
            dst[j*dim+i+1] = t2;
            dst[j*dim+i+2] = t3;
            dst[j*dim+i+3] = t4;
            j++;
        }
    }
    while(i < dim){
        for(j = 0; j < dim-3; j+=4){
            int t1 = src[i*dim+j];
            int t2 = src[i*dim+j+1];
            int t3 = src[i*dim+j+2];
            int t4 = src[i*dim+j+3];
            dst[j*dim+i] = t1;
            dst[(j+1)*dim+i] = t2;
            dst[(j+2)*dim+i] = t3;
            dst[(j+3)*dim+i] = t4;
        }
        while(j < dim){
            dst[j*dim+i] = src[i*dim+j];
            j++;
        }
        i++;
        //之前这里忘记++了QAQ
    }
}

