/*************************************************************************
    > File Name: proxy.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月27日 星期日 23时26分25秒
 ************************************************************************/

#include "csapp.h"
#include "cache.h"

#ifndef PROXY_H
#define PROXY_H
typedef struct{
    int connfd;
    struct sockaddr_storage clientaddr;
    socklen_t clientlen;
    char hostname[32];
    char port[32];
    struct cbuf *cep;
}client;

void doit(int connfd, struct cbuf *cep);
void clienterror(int connfd, char *cause, char *errnum,
        char *shortmsg, char *longmsg);
int parseurl(char *url, char *uri, char *host, char *port);
int read_requesthdrs(rio_t *rp);
int send_requesthdrs(rio_t *rp, int connfd, int clientfd, char *host);
char *get_resource(int connfd, int clientfd, int *clen);
void e504(int connfd, char *url, char *host, char *port);
void e501(int connfd, char *cause);

void *serv_thread(void *vargp);
#endif

