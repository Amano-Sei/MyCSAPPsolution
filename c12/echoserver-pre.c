/*************************************************************************
    > File Name: echoserver-pre.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月19日 星期六 22时01分20秒
 ************************************************************************/

#include "csapp.h"
#define NTHREADS 4
#define SBUFSIZE 16

//因为想重新熟悉一下生产者消费者问题，所以敲了一遍。

typedef struct{
    int *buf;
    int n;
    int front;
    int rear;
    sem_t mutex;
    sem_t slots;
    sem_t items;
}sbuf_t;

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
int sbuf_remove(sbuf_t *sp);

void echo_cnt(int connfd);
void *thread(void *vargp);

sbuf_t sbuf;

int main(int argc, char **argv){
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]);

    sbuf_init(&sbuf, SBUFSIZE);
    for(int i = 0; i < NTHREADS; i++)
        Pthread_create(&tid, NULL, thread, NULL);
    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
        sbuf_insert(&sbuf, connfd);
    }

    return 0;
}

void *thread(void *vargp){
    Pthread_detach(pthread_self());

    while(1){
        int connfd = sbuf_remove(&sbuf);
        echo_cnt(connfd);
        Close(connfd);
    }
    return NULL;
}

void sbuf_init(sbuf_t *sp, int n){
    sp->buf = Calloc(n, sizeof(int));
    sp->n = n;
    sp->front = sp->rear = 0;
    Sem_init(&sp->mutex, 0, 1);
    Sem_init(&sp->slots, 0, n);
    Sem_init(&sp->items, 0, 0);
}

void sbuf_deinit(sbuf_t *sp){
    Free(sp->buf);
}

void sbuf_insert(sbuf_t *sp, int item){
    P(&sp->slots);
    //果不出其然这里写出锅
    //这里要注意p的顺序
    P(&sp->mutex);
    sp->buf[(++sp->rear)%(sp->n)] = item;
    V(&sp->mutex);
    V(&sp->items);
}

int sbuf_remove(sbuf_t *sp){
    int item;
    P(&sp->items);
    P(&sp->mutex);
    item = sp->buf[(++sp->front)%(sp->n)];
    V(&sp->mutex);
    V(&sp->slots);
    return item;
}

