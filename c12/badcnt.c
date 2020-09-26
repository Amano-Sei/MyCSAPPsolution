/*************************************************************************
    > File Name: badcnt.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月17日 星期四 22时48分20秒
 ************************************************************************/

#include "csapp.h"

void *thread(void *vargp);

volatile long cnt = 0;

int main(int argc, char **argv){
    long niters;
    pthread_t tid1, tid2;
    if(argc != 2){
        fprintf(stderr, "usage: %s <niter>\n", argv[0]);
        exit(0);
    }
    niters = atoi(argv[1]);

    Pthread_create(&tid1, NULL, thread, (void *)&niters);
    Pthread_create(&tid2, NULL, thread, (void *)&niters);

    Pthread_join(tid1, NULL);
    Pthread_join(tid2, NULL);

    if(cnt != 2*niters)
        printf("BOOM! cnt=%ld\n", cnt);
    else
        printf("OK cnt=%ld\n", cnt);
    exit(0);
}

void *thread(void *vargp){
    long niters = *(long *)vargp;
    for(long i = 0; i < niters; i++)
        cnt++;
    return NULL;
}

