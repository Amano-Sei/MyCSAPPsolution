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
    for(i = 0; i < N-7; i+=8){
        for(j = 0; j < M-7; j+=8){
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

            t1 = A[i+1][j];
            t2 = A[i+1][j+1];
            t3 = A[i+1][j+2];
            t4 = A[i+1][j+3];
            t5 = A[i+1][j+4];
            t6 = A[i+1][j+5];
            t7 = A[i+1][j+6];
            t8 = A[i+1][j+7];
            B[j][i+1] = t1;
            B[j+1][i+1] = t2;
            B[j+2][i+1] = t3;
            B[j+3][i+1] = t4;
            B[j+4][i+1] = t5;
            B[j+5][i+1] = t6;
            B[j+6][i+1] = t7;
            B[j+7][i+1] = t8;

            t1 = A[i+2][j];
            t2 = A[i+2][j+1];
            t3 = A[i+2][j+2];
            t4 = A[i+2][j+3];
            t5 = A[i+2][j+4];
            t6 = A[i+2][j+5];
            t7 = A[i+2][j+6];
            t8 = A[i+2][j+7];
            B[j][i+2] = t1;
            B[j+1][i+2] = t2;
            B[j+2][i+2] = t3;
            B[j+3][i+2] = t4;
            B[j+4][i+2] = t5;
            B[j+5][i+2] = t6;
            B[j+6][i+2] = t7;
            B[j+7][i+2] = t8;

            t1 = A[i+3][j];
            t2 = A[i+3][j+1];
            t3 = A[i+3][j+2];
            t4 = A[i+3][j+3];
            t5 = A[i+3][j+4];
            t6 = A[i+3][j+5];
            t7 = A[i+3][j+6];
            t8 = A[i+3][j+7];
            B[j][i+3] = t1;
            B[j+1][i+3] = t2;
            B[j+2][i+3] = t3;
            B[j+3][i+3] = t4;
            B[j+4][i+3] = t5;
            B[j+5][i+3] = t6;
            B[j+6][i+3] = t7;
            B[j+7][i+3] = t8;

            t1 = A[i+4][j];
            t2 = A[i+4][j+1];
            t3 = A[i+4][j+2];
            t4 = A[i+4][j+3];
            t5 = A[i+4][j+4];
            t6 = A[i+4][j+5];
            t7 = A[i+4][j+6];
            t8 = A[i+4][j+7];
            B[j][i+4] = t1;
            B[j+1][i+4] = t2;
            B[j+2][i+4] = t3;
            B[j+3][i+4] = t4;
            B[j+4][i+4] = t5;
            B[j+5][i+4] = t6;
            B[j+6][i+4] = t7;
            B[j+7][i+4] = t8;

            t1 = A[i+5][j];
            t2 = A[i+5][j+1];
            t3 = A[i+5][j+2];
            t4 = A[i+5][j+3];
            t5 = A[i+5][j+4];
            t6 = A[i+5][j+5];
            t7 = A[i+5][j+6];
            t8 = A[i+5][j+7];
            B[j][i+5] = t1;
            B[j+1][i+5] = t2;
            B[j+2][i+5] = t3;
            B[j+3][i+5] = t4;
            B[j+4][i+5] = t5;
            B[j+5][i+5] = t6;
            B[j+6][i+5] = t7;
            B[j+7][i+5] = t8;

            t1 = A[i+6][j];
            t2 = A[i+6][j+1];
            t3 = A[i+6][j+2];
            t4 = A[i+6][j+3];
            t5 = A[i+6][j+4];
            t6 = A[i+6][j+5];
            t7 = A[i+6][j+6];
            t8 = A[i+6][j+7];
            B[j][i+6] = t1;
            B[j+1][i+6] = t2;
            B[j+2][i+6] = t3;
            B[j+3][i+6] = t4;
            B[j+4][i+6] = t5;
            B[j+5][i+6] = t6;
            B[j+6][i+6] = t7;
            B[j+7][i+6] = t8;

            t1 = A[i+7][j];
            t2 = A[i+7][j+1];
            t3 = A[i+7][j+2];
            t4 = A[i+7][j+3];
            t5 = A[i+7][j+4];
            t6 = A[i+7][j+5];
            t7 = A[i+7][j+6];
            t8 = A[i+7][j+7];
            B[j][i+7] = t1;
            B[j+1][i+7] = t2;
            B[j+2][i+7] = t3;
            B[j+3][i+7] = t4;
            B[j+4][i+7] = t5;
            B[j+5][i+7] = t6;
            B[j+6][i+7] = t7;
            B[j+7][i+7] = t8;
        }
        while(j < M){
            int t1 = A[i][j];
            int t2 = A[i+1][j];
            int t3 = A[i+2][j];
            int t4 = A[i+3][j];
            int t5 = A[i+4][j];
            int t6 = A[i+5][j];
            int t7 = A[i+6][j];
            int t8 = A[i+7][j];
            B[j][i] = t1;
            B[j][i+1] = t2;
            B[j][i+2] = t3;
            B[j][i+3] = t4;
            B[j][i+4] = t5;
            B[j][i+5] = t6;
            B[j][i+6] = t7;
            B[j][i+7] = t8;
            j++;
        }
    }
    while(i < N){
        for(j = 0; j < M-7; j+=8){
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
            B[j][i] = A[i][j];
            j++;
        }
        i++;
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

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

