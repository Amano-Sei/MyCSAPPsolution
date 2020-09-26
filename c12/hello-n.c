/*************************************************************************
    > File Name: hello-n.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月21日 星期一 16时19分46秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 10

void *thread(void *vargp);

pthread_t tid[MAXN];

int main(int argc, char **argv){
    int niters;
    int ret;
    if(argc != 2){
        fprintf(stderr, "usage: %s <number>\n", argv[0]);
        exit(0);
    }
    niters = atoi(argv[1]);
    if(niters > MAXN){
        fprintf(stderr, "%s is too big, %d is the maximum\n", argv[1], MAXN);
        niters = MAXN;
    }
    for(int i = 0; i < niters; i++){
        ret = pthread_create(&tid[i], NULL, thread, NULL);
        if(ret){
            fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
            exit(0);
        }
    }
    for(int i = 0; i < niters; i++){
        ret = pthread_join(tid[i], NULL);
        if(ret){
            fprintf(stderr, "pthread_join error: %s\n", strerror(ret));
            exit(0);
        }
    }
    return 0;
}

void *thread(void *vargp){
    puts("Hello, world!");
    return NULL;
}

