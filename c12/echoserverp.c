/*************************************************************************
    > File Name: echoserverp.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月13日 星期日 22时08分57秒
 ************************************************************************/

#include "csapp.h"

void echo(int connfd, char *from);

void sigchld_handler(int signum){
    int old_errno = errno;
    while(waitpid(-1, NULL, WNOHANG) > 0);
    if(errno != ECHILD)
        unix_error("sigchld_handler error");
    errno = old_errno;
}

int main(int argc, char **argv){
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    Signal(SIGCHLD, sigchld_handler);
    listenfd = Open_listenfd(argv[1]);
    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        if(Fork() == 0){
            char *hosp = malloc(32);
            char *serp = malloc(32);
            Getnameinfo((struct sockaddr *)&clientaddr, clientlen, hosp, 32, serp, 32, NI_NUMERICHOST|NI_NUMERICSERV);
            strcat(hosp, ":");
            strcat(hosp, serp);
            free(serp);
            Close(listenfd);
            echo(connfd, hosp);
            free(hosp);
            Close(connfd);
            exit(0);
        }
        Close(connfd);
    }
    return 0;
}

void echo(int connfd, char *from){
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    Rio_readinitb(&rio, connfd);
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) != 0){
        printf("server received %lu bytes from %s: %s\n", n, from, buf);
        Rio_writen(connfd, buf, n);
    }
}

