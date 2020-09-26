/*************************************************************************
    > File Name: tfgets-thread-2.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月23日 星期三 15时49分15秒
 ************************************************************************/

#define _GNU_SOURCE
#include "csapp.h"

struct getsarg{
    char *s;
    int size;
    FILE *stream;
};

//基于带有timeout的join的pthread_timedjoin_np的安全可靠的方法

void *reader(void *vargp);

char *tfgets(char *s, int size, FILE *stream){
    pthread_t tid;
    char *ret = NULL;
    struct timespec fivesec;
    struct getsarg args;
    int retcode;

    args.s = s;
    args.size = size;
    args.stream = stream;

    Pthread_create(&tid, NULL, reader, &args);

    if(clock_gettime(CLOCK_REALTIME, &fivesec) == -1){
        fprintf(stderr, "clock_gettime error: %s\n", strerror(errno));
        exit(0);
    }
    fivesec.tv_sec += 5;

    if(retcode = pthread_timedjoin_np(tid, (void **)&ret, &fivesec)){
        if(retcode != ETIMEDOUT){
            fprintf(stderr, "pthread_timedjoin_np error: %s\n", strerror(retcode));
            exit(0);
        }
        pthread_cancel(tid);
        ret = NULL;
        pthread_join(tid, NULL);
    }
    return ret;
}

void *reader(void *vargp){
    struct getsarg *p = vargp;
    return fgets(p->s, p->size, p->stream);
}

