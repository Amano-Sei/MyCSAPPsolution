/*************************************************************************
    > File Name: sbuf.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月25日 星期五 16时17分24秒
 ************************************************************************/

#include "csapp.h"
#include "sbuf.h"

void sbuf_init(sbuf_t *sp, int n){
    sp->buf = Calloc(n, sizeof(int));
    sp->n = n;
    sp->front = sp->rear = 0;
    Sem_init(&sp->mutex, 0, 1);
    Sem_init(&sp->slots, 0, n);
    Sem_init(&sp->items, 0, 0);

    for(int i = 0; i < MAXTHREAD; i++)
        Sem_init(&sp->threads[i], 0, 1);
    sp->tcnt = MINTHREAD;
    for(int i = 0; i < MINTHREAD; i++)
        Pthread_create(&sp->tid[i], NULL, serv_thread, (void *)i);
}

void sbuf_deinit(sbuf_t *sp){
    free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item){
    P(&sp->slots);
    P(&sp->mutex);
    sp->buf[(++sp->rear)%(sp->n)] = item;
    if(sp->rear == sp->front+sp->n){
        fprintf(stderr, " + adding...\n");
        register int tcnt = sp->tcnt;
        if(tcnt < MAXTHREAD){
            for(int i = tcnt; i < 2*tcnt; i++)
                Pthread_create(&sp->tid[i], NULL, serv_thread, (void *)i);
            fprintf(stderr, " + the number of threads has been changed from %d to %d\n", tcnt, tcnt*2);
            sp->tcnt = tcnt*2;
        }else
            fprintf(stderr, " + Couldn't create more threads.\n");
    }
    V(&sp->mutex);
    V(&sp->items);
}

void sbuf_remove(sbuf_t *sp, int tid){
    printf(" > thread %d is running...\n", tid);
    int connfd;
    pthread_t tmp;
    int tmpc;
    P(&sp->items);
    P(&sp->mutex);
    P(&sp->threads[tid]);
    connfd = sp->buf[(++sp->front)%(sp->n)];
    printf(" > thread %d get connfd: %d...\n", tid, connfd);
    if(sp->front < sp->rear)
        V(&sp->mutex);
    else{
        register int cnt = 0;
        for(int i = sp->tcnt-1; i >= 0; i--){
            sem_getvalue(&sp->threads[i], &tmpc);
            cnt += tmpc;
        }
        if(cnt*2 > sp->tcnt)
            Pthread_create(&tmp, NULL, less_thread, sp);
        else
            V(&sp->mutex);
    }
    V(&sp->slots);
    //sleep(5);
    doit(connfd);
    Close(connfd);
    printf(" > thread %d has closed %d...\n", tid, connfd);
    V(&sp->threads[tid]);
}

void *less_thread(void *vargp){
    fprintf(stderr, " - subing...\n");
    sbuf_t *sp = vargp;
    Pthread_detach(pthread_self());
    register int tcnt = sp->tcnt;
    if(tcnt > MINTHREAD){
        for(int i = tcnt/2; i < tcnt; i++){
            fprintf(stderr, " - canceling %d...\n", i);
            P(&sp->threads[i]);
            Pthread_cancel(sp->tid[i]);
            Pthread_join(sp->tid[i], NULL);
            V(&sp->threads[i]);
            fprintf(stderr, " - cancel %d done...\n", i);
        }
        fprintf(stderr, " - the number of threads has been changed from %d to %d\n", tcnt, tcnt/2);
        sp->tcnt = tcnt/2;
    }else
        fprintf(stderr, " - Couldn't make threads less.\n");
    V(&sp->mutex);
}

