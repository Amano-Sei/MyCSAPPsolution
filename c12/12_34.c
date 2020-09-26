/*************************************************************************
    > File Name: 12_34.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月23日 星期三 16时22分52秒
 ************************************************************************/

#include "csapp.h"



struct baseargs{
    int m, n, q;
    int **a, **b, **ans;
};
struct calcargs{
    int ci;
    struct baseargs *recs;
};

void *calcthread(void *vargp){
    struct calcargs *p = vargp;
    int ci = p->ci;
    int cans;
    int **a = p->recs->a;
    int **b = p->recs->b;
    for(int i = p->recs->q-1; i >= 0; i--){
        cans = 0;
        for(int j = p->recs->n-1; j >= 0; j--)
            cans += a[ci][j]*b[j][i];
        p->recs->ans[ci][i] = cans;
    }
    return NULL;
}

int **calcrec(int **A, int **B, int m, int n, int q){
    register int **ret = Malloc(m*sizeof(int *));
    pthread_t *tids = Malloc(m*sizeof(pthread_t));
    struct baseargs ba = { m, n, q, A, B, ret };
    struct calcargs *ca = Malloc(m * sizeof(struct calcargs));

    for(int i = 0; i < m ;i++){
        ret[i] = Malloc(q*sizeof(int));
        ca[i].recs = &ba;
        ca[i].ci = i;
        Pthread_create(&tids[i], NULL, calcthread, &ca[i]);
    }
    for(int i = 0; i < m; i++)
        Pthread_join(tids[i], NULL);

    free(tids);
    free(ca);

    return ret;
}

