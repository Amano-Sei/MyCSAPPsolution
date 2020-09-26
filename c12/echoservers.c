/*************************************************************************
    > File Name: echoservers.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月16日 星期三 22时09分53秒
 ************************************************************************/

#include "csapp.h"

typedef struct{
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    //其实这个里面有个问题，maxi和maxfd只会变大不会变小
    //不过不会出现错误
    int clientfd[FD_SETSIZE];
    char clientfrom[FD_SETSIZE][32];
    rio_t clientrio[FD_SETSIZE];
}pool;

int byte_cnt = 0;

void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p, char *host, char *port);
void check_clients(pool *p);

int main(int argc, char **argv){
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;
    char host[32], port[32];

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while(1){
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &pool.ready_set)){
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            Getnameinfo((struct sockaddr *)&clientaddr, clientlen, host, 32, port, 32, NI_NUMERICHOST|NI_NUMERICSERV);
            add_client(connfd, &pool, host, port);
        }
        check_clients(&pool);
    }
}

void init_pool(int listenfd, pool *p){
    p->maxi = -1;
    for(int i = 0; i < FD_SETSIZE; i++)
        p->clientfd[i] = -1;
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p, char *host, char *port){
    int i;
    p->nready--;
    for(i = 0; i < FD_SETSIZE; i++)
        if(p->clientfd[i] < 0){
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);
            strcpy(p->clientfrom[i], host);
            strcat(p->clientfrom[i], ":");
            strcat(p->clientfrom[i], port);

            FD_SET(connfd, &p->read_set);

            if(connfd > p->maxfd)
                p->maxfd = connfd;
            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    if(i == FD_SETSIZE)
        app_error("add_client error: Too many clients");
}

void check_clients(pool *p){
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for(i = 0; i <= p->maxi && p->nready > 0; i++){
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if(connfd > 0 && FD_ISSET(connfd, &p->ready_set)){
            p->nready--;
            if((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d from %s\n", n, byte_cnt, connfd, p->clientfrom[i]);
                Rio_writen(connfd, buf, n);
            }else{
                printf("Connection from %s on fd %d closed.\n", p->clientfrom[i], connfd);
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}

