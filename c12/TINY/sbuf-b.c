/*************************************************************************
    > File Name: sbuf.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月25日 星期五 16时17分24秒
 ************************************************************************/

#include "csapp.h"
#include "sbuf-b.h"

void sbuf_init(sbuf_t *sp, int n){
    pthread_t tmp;
    sp->buf = Calloc(n, sizeof(int));
    sp->n = n;
    sp->front = sp->rear = 0;
    Sem_init(&sp->mutex, 0, 1);
    Sem_init(&sp->slots, 0, n);
    Sem_init(&sp->items, 0, 0);

    Sem_init(&sp->entry, 0, 1);

    for(int i = 0; i < MAXTHREAD; i++)
        Sem_init(&sp->threads[i], 0, 1);
    sp->tcnt = MINTHREAD;
    for(int i = 0; i < MINTHREAD; i++)
        Pthread_create(&sp->tid[i], NULL, serv_thread, (void *)i);
    Pthread_create(&tmp, NULL, check_thread, sp);
}

void sbuf_deinit(sbuf_t *sp){
    free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item){
    P(&sp->slots);
    P(&sp->mutex);
    sp->buf[(++sp->rear)%(sp->n)] = item;
    V(&sp->mutex);
    V(&sp->items);
}

int sbuf_remove(sbuf_t *sp){
    int connfd;

    P(&sp->items);
    P(&sp->mutex);
    connfd = sp->buf[(++sp->front)%(sp->n)];
    V(&sp->mutex);
    V(&sp->slots);

    return connfd;
}

