/*************************************************************************
    > File Name: 6_46.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月26日 星期六 19时45分08秒
 ************************************************************************/

#include <stdio.h>

/*
 * 看到这道题，显然这里沿着对角线对称的两个点各读一次
 * 然后如果一侧为1但是另一侧不为1，把不为1的那一侧写入1
 * 但是这样没有一个稳定的预测方法，可能会因为频繁的预测惩罚
 * 导致更差的性能，所以索性计算结果直接全部写回去好了
 * 不过还是写两个版本吧
 *
 * 展开想用4*4的小矩阵，细节上来说对角线处需要注意（其实想写2*2（懒
 * 读的话先读出一侧一列4个，然后读另一侧一行4个
 * 然后写入那一侧一行4个，最后写回来这边一列
 * 基本思路还是优先确保行4个的缓存命中率
 *
 * 写完后感觉主要区别点还是在对角线处的细节
 */

void naive_col_convert(int *G, int dim){
    int i, j;
    for(i = 0; i < dim; i++)
        for(j = 0; j < dim; j++)
            G[j*dim+i] = G[j*dim+i]||G[i*dim+j];
}

void my_col_convert(int *G, int dim){
    int i, j;
    for(i = 0; i < dim-4; i+=4){
        int t1 = G[(i+1)*dim+i];
        int t2 = G[(i+2)*dim+i];
        int t3 = G[(i+3)*dim+i];
        int t4 = G[(i+4)*dim+i];
        t1 = t1 || G[i*dim+i+1];
        t2 = t2 || G[i*dim+i+2];
        t3 = t3 || G[i*dim+i+3];
        t4 = t4 || G[i*dim+i+4];
        G[i*dim+i+1] = t1;
        G[i*dim+i+2] = t2;
        G[i*dim+i+3] = t3;
        G[i*dim+i+4] = t4;
        G[(i+1)*dim+i] = t1;
        G[(i+2)*dim+i] = t2;
        G[(i+3)*dim+i] = t3;
        G[(i+4)*dim+i] = t4;

        t1 = G[(i+4)*dim+i+3];
        t2 = G[(i+2)*dim+i+1];
        t3 = G[(i+3)*dim+i+1];
        t4 = G[(i+4)*dim+i+1];
        t1 = t1 || G[(i+3)*dim+i+4];
        t2 = t2 || G[(i+1)*dim+i+2];
        t3 = t3 || G[(i+1)*dim+i+3];
        t4 = t4 || G[(i+1)*dim+i+4];
        G[(i+3)*dim+i+4] = t1;
        G[(i+1)*dim+i+2] = t2;
        G[(i+1)*dim+i+3] = t3;
        G[(i+1)*dim+i+4] = t4;
        G[(i+4)*dim+i+3] = t1;
        G[(i+2)*dim+i+1] = t2;
        G[(i+3)*dim+i+1] = t3;
        G[(i+4)*dim+i+1] = t4;
        
        t3 = G[(i+3)*dim+i+2];
        t4 = G[(i+4)*dim+i+2];
        t3 = t3 || G[(i+2)*dim+i+3];
        t4 = t4 || G[(i+2)*dim+i+4];
        G[(i+2)*dim+i+3] = t3;
        G[(i+2)*dim+i+4] = t4;
        G[(i+3)*dim+i+2] = t3;
        G[(i+4)*dim+i+2] = t4;
        for(j = i+5; j < dim-3; j+=4){
            int t1 = G[j*dim+i];
            int t2 = G[(j+1)*dim+i];
            int t3 = G[(j+2)*dim+i];
            int t4 = G[(j+3)*dim+i];
            t1 = t1 || G[i*dim+j];
            t2 = t2 || G[i*dim+j+1];
            t3 = t3 || G[i*dim+j+2];
            t4 = t4 || G[i*dim+j+3];
            G[i*dim+j] = t1;
            G[i*dim+j+1] = t2;
            G[i*dim+j+2] = t3;
            G[i*dim+j+3] = t4;
            G[j*dim+i] = t1;
            G[(j+1)*dim+i] = t2;
            G[(j+2)*dim+i] = t3;
            G[(j+3)*dim+i] = t4;
            
            t1 = G[j*dim+i+1];
            t2 = G[(j+1)*dim+i+1];
            t3 = G[(j+2)*dim+i+1];
            t4 = G[(j+3)*dim+i+1];
            t1 = t1 || G[(i+1)*dim+j];
            t2 = t2 || G[(i+1)*dim+j+1];
            t3 = t3 || G[(i+1)*dim+j+2];
            t4 = t4 || G[(i+1)*dim+j+3];
            G[(i+1)*dim+j] = t1;
            G[(i+1)*dim+j+1] = t2;
            G[(i+1)*dim+j+2] = t3;
            G[(i+1)*dim+j+3] = t4;
            G[j*dim+i+1] = t1;
            G[(j+1)*dim+i+1] = t2;
            G[(j+2)*dim+i+1] = t3;
            G[(j+3)*dim+i+1] = t4;
            
            t1 = G[j*dim+i+2];
            t2 = G[(j+1)*dim+i+2];
            t3 = G[(j+2)*dim+i+2];
            t4 = G[(j+3)*dim+i+2];
            t1 = t1 || G[(i+2)*dim+j];
            t2 = t2 || G[(i+2)*dim+j+1];
            t3 = t3 || G[(i+2)*dim+j+2];
            t4 = t4 || G[(i+2)*dim+j+3];
            G[(i+2)*dim+j] = t1;
            G[(i+2)*dim+j+1] = t2;
            G[(i+2)*dim+j+2] = t3;
            G[(i+2)*dim+j+3] = t4;
            G[j*dim+i+2] = t1;
            G[(j+1)*dim+i+2] = t2;
            G[(j+2)*dim+i+2] = t3;
            G[(j+3)*dim+i+2] = t4;
            
            t1 = G[j*dim+i+3];
            t2 = G[(j+1)*dim+i+3];
            t3 = G[(j+2)*dim+i+3];
            t4 = G[(j+3)*dim+i+3];
            t1 = t1 || G[(i+3)*dim+j];
            t2 = t2 || G[(i+3)*dim+j+1];
            t3 = t3 || G[(i+3)*dim+j+2];
            t4 = t4 || G[(i+3)*dim+j+3];
            G[(i+3)*dim+j] = t1;
            G[(i+3)*dim+j+1] = t2;
            G[(i+3)*dim+j+2] = t3;
            G[(i+3)*dim+j+3] = t4;
            G[j*dim+i+3] = t1;
            G[(j+1)*dim+i+3] = t2;
            G[(j+2)*dim+i+3] = t3;
            G[(j+3)*dim+i+3] = t4;
        }
        while(j < dim){
            int t1 = G[i*dim+j];
            int t2 = G[(i+1)*dim+j];
            int t3 = G[(i+2)*dim+j];
            int t4 = G[(i+3)*dim+j];
            t1 = t1 || G[j*dim+i];
            t2 = t2 || G[j*dim+i+1];
            t3 = t3 || G[j*dim+i+2];
            t4 = t4 || G[j*dim+i+3];
            G[j*dim+i] = t1;
            G[j*dim+i+1] = t2;
            G[j*dim+i+2] = t3;
            G[j*dim+i+3] = t4;
            j++;
        }
    }
    while(i < dim-1)
        for(j = i+1; j < dim; j++){
            int t1 = G[i*dim+j];
            t1 = t1 || G[j*dim+i];
            G[j*dim+i] = t1;
            G[i*dim+j] = t1;
        }
}

