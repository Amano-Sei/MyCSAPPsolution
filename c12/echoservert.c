/*************************************************************************
    > File Name: echoservert.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月17日 星期四 16时17分48秒
 ************************************************************************/

#include "csapp.h"

void echo(int connfd);
void *thread(void *vargp);

int main(int argc, char **argv){
    int listenfd, *connfdp;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pthread_t tid;

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    listenfd = Open_listenfd(argv[1]);

    while(1){
        clientlen = sizeof(clientaddr);
        connfdp = Malloc(sizeof(int));
        *connfdp = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        pthread_create(&tid, NULL, thread, connfdp);
    }

    return 0;
}

void echo(int connfd){
    char buf[MAXLINE];
    rio_t rio;
    size_t n;
    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
        printf("server received %d bytes]\n", (int)n);
        Rio_writen(connfd, buf, n);
    }
}

void *thread(void *vargp){
    int connfd = *(int *)vargp;
    Pthread_detach(Pthread_self());
    free(vargp);
    echo(connfd);
    Close(connfd);
    return NULL;
}

