/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

#define ROWNUM 27
#define COLNUM 16

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;
    int t1, t2, t3, t4, t5, t6, t7, t8;
    if(N == 32 && M == 32){
        for(int i = 0; i <= 28; i+=8)
            for(int j = 0; j <= 28; j+=8){
                for(int ii = i; ii < i+8; ii++){
                    t1 = A[ii][j];
                    t2 = A[ii][j+1];
                    t3 = A[ii][j+2];
                    t4 = A[ii][j+3];
                    t5 = A[ii][j+4];
                    t6 = A[ii][j+5];
                    t7 = A[ii][j+6];
                    t8 = A[ii][j+7];
                    B[j+ii-i][i] = t1;
                    B[j+ii-i][i+1] = t2;
                    B[j+ii-i][i+2] = t3;
                    B[j+ii-i][i+3] = t4;
                    B[j+ii-i][i+4] = t5;
                    B[j+ii-i][i+5] = t6;
                    B[j+ii-i][i+6] = t7;
                    B[j+ii-i][i+7] = t8;
                }
                for(int ii = 0; ii < 7; ii++)
                    for(int jj = ii+1; jj < 8; jj++){
                        t1 = B[j+jj][i+ii];
                        B[j+jj][i+ii] = B[j+ii][i+jj];
                        B[j+ii][i+jj] = t1;
                    }
            }
    }else if(N == 64 && M == 64){
        for(i = 0; i <= 56; i+=8){
            for(j = 0; j <= 56; j+=8){
                for(int ii = i; ii < i+4; ii++){
                    t1 = A[ii][j];
                    t2 = A[ii][j+1];
                    t3 = A[ii][j+2];
                    t4 = A[ii][j+3];
                    t5 = A[ii][j+4];
                    t6 = A[ii][j+5];
                    t7 = A[ii][j+6];
                    t8 = A[ii][j+7];
                    B[j][ii] = t1;
                    B[j+1][ii] = t2;
                    B[j+2][ii] = t3;
                    B[j+3][ii] = t4;
                    B[j][ii+4] = t5;
                    B[j+1][ii+4] = t6;
                    B[j+2][ii+4] = t7;
                    B[j+3][ii+4] = t8;
                }
                for(int jj = j; jj < j+4; jj++){
                    t1 = A[i+4][jj];
                    t2 = A[i+5][jj];
                    t3 = A[i+6][jj];
                    t4 = A[i+7][jj];
                    t5 = B[jj][i+4];
                    t6 = B[jj][i+5];
                    t7 = B[jj][i+6];
                    t8 = B[jj][i+7];
                    B[jj][i+4] = t1;
                    B[jj][i+5] = t2;
                    B[jj][i+6] = t3;
                    B[jj][i+7] = t4;
                    B[jj+4][i] = t5;
                    B[jj+4][i+1] = t6;
                    B[jj+4][i+2] = t7;
                    B[jj+4][i+3] = t8;
                }
                t1 = A[i+4][j+4];
                t2 = A[i+4][j+5];
                t3 = A[i+4][j+6];
                t4 = A[i+4][j+7];
                t5 = A[i+5][j+4];
                t6 = A[i+5][j+5];
                t7 = A[i+5][j+6];
                t8 = A[i+5][j+7];
                B[j+4][i+4] = t1;
                B[j+5][i+4] = t2;
                B[j+4][i+6] = t3;
                B[j+5][i+6] = t4;
                B[j+4][i+5] = t5;
                B[j+5][i+5] = t6;
                B[j+4][i+7] = t7;
                B[j+5][i+7] = t8;

                t1 = A[i+6][j+4];
                t2 = A[i+6][j+5];
                t3 = A[i+7][j+4];
                t4 = A[i+7][j+5];
                t5 = B[j+4][i+6];
                t6 = B[j+4][i+7];
                t7 = B[j+5][i+6];
                t8 = B[j+5][i+7];
                B[j+4][i+6] = t1;
                B[j+5][i+6] = t2;
                B[j+4][i+7] = t3;
                B[j+5][i+7] = t4;

                t1 = A[i+6][j+6];
                t2 = A[i+6][j+7];
                t3 = A[i+7][j+6];
                t4 = A[i+7][j+7];
                B[j+6][i+4] = t5;
                B[j+6][i+5] = t6;
                B[j+6][i+6] = t1;
                B[j+6][i+7] = t3;
                B[j+7][i+4] = t7;
                B[j+7][i+5] = t8;
                B[j+7][i+6] = t2;
                B[j+7][i+7] = t4;
            }
        }
    }else
        for(i = 0; i < N; i+=ROWNUM)
            for(j = 0; j < M; j+=COLNUM)
                for(int ii = i; ii < i+ROWNUM && ii < N; ii++)
                    for(int jj = j; jj < j+COLNUM && jj < M; jj++)
                        B[jj][ii] = A[ii][jj];
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 
char transpose_303_desc[] = "303";
void transpose_303(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;
    int t1, t2, t3, t4, t5, t6, t7, t8;
    for(i = 0; i <= N-8; i+=8){
        for(j = 0; j <= M-8; j+=8){
            for(int ii = i; ii < i+4; ii++){
                t1 = A[ii][j];
                t2 = A[ii][j+1];
                t3 = A[ii][j+2];
                t4 = A[ii][j+3];
                t5 = A[ii][j+4];
                t6 = A[ii][j+5];
                t7 = A[ii][j+6];
                t8 = A[ii][j+7];
                B[j][ii] = t1;
                B[j+1][ii] = t2;
                B[j+2][ii] = t3;
                B[j+3][ii] = t4;
                B[j][ii+4] = t5;
                B[j+1][ii+4] = t6;
                B[j+2][ii+4] = t7;
                B[j+3][ii+4] = t8;
            }
            for(int jj = j; jj < j+4; jj++){
                t1 = A[i+4][jj];
                t2 = A[i+5][jj];
                t3 = A[i+6][jj];
                t4 = A[i+7][jj];
                t5 = B[jj][i+4];
                t6 = B[jj][i+5];
                t7 = B[jj][i+6];
                t8 = B[jj][i+7];
                B[jj][i+4] = t1;
                B[jj][i+5] = t2;
                B[jj][i+6] = t3;
                B[jj][i+7] = t4;
                B[jj+4][i] = t5;
                B[jj+4][i+1] = t6;
                B[jj+4][i+2] = t7;
                B[jj+4][i+3] = t8;
            }
            t1 = A[i+4][j+4];
            t2 = A[i+4][j+5];
            t3 = A[i+4][j+6];
            t4 = A[i+4][j+7];
            t5 = A[i+5][j+4];
            t6 = A[i+5][j+5];
            t7 = A[i+5][j+6];
            t8 = A[i+5][j+7];
            B[j+4][i+4] = t1;
            B[j+5][i+4] = t2;
            B[j+4][i+6] = t3;
            B[j+5][i+6] = t4;
            B[j+4][i+5] = t5;
            B[j+5][i+5] = t6;
            B[j+4][i+7] = t7;
            B[j+5][i+7] = t8;

            t1 = A[i+6][j+4];
            t2 = A[i+6][j+5];
            t3 = A[i+7][j+4];
            t4 = A[i+7][j+5];
            t5 = B[j+4][i+6];
            t6 = B[j+4][i+7];
            t7 = B[j+5][i+6];
            t8 = B[j+5][i+7];
            B[j+4][i+6] = t1;
            B[j+5][i+6] = t2;
            B[j+4][i+7] = t3;
            B[j+5][i+7] = t4;

            t1 = A[i+6][j+6];
            t2 = A[i+6][j+7];
            t3 = A[i+7][j+6];
            t4 = A[i+7][j+7];
            B[j+6][i+4] = t5;
            B[j+6][i+5] = t6;
            B[j+6][i+6] = t1;
            B[j+6][i+7] = t3;
            B[j+7][i+4] = t7;
            B[j+7][i+5] = t8;
            B[j+7][i+6] = t2;
            B[j+7][i+7] = t4;
        }
        while(j < M){
            for(int ii = i; ii<i+8; ii++){
                int t1 = A[ii][j];
                int t2 = A[ii][j+1];
                int t3 = A[ii][j+2];
                int t4 = A[ii][j+3];
                int t5 = A[ii][j+4];
                int t6 = A[ii][j+5];
                int t7 = A[ii][j+6];
                int t8 = A[ii][j+7];
                B[j][ii] = t1;
                B[j+1][ii] = t2;
                B[j+2][ii] = t3;
                B[j+3][ii] = t4;
                B[j+4][ii] = t5;
                B[j+5][ii] = t6;
                B[j+6][ii] = t7;
                B[j+7][ii] = t8;
            }
            j++;
        }
    }
    while(i < N){
        for(j = 0; j <= M-8; j+=8){
            int t1 = A[i][j];
            int t2 = A[i][j+1];
            int t3 = A[i][j+2];
            int t4 = A[i][j+3];
            int t5 = A[i][j+4];
            int t6 = A[i][j+5];
            int t7 = A[i][j+6];
            int t8 = A[i][j+7];
            B[j][i] = t1;
            B[j+1][i] = t2;
            B[j+2][i] = t3;
            B[j+3][i] = t4;
            B[j+4][i] = t5;
            B[j+5][i] = t6;
            B[j+6][i] = t7;
            B[j+7][i] = t8;
        }
        while(j < M){
            int t1 = A[i][j];
            B[j][i] = t1;
            j++;
        }
        i++;
    }
}


/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

    registerTransFunction(transpose_303, transpose_303_desc); 
}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

