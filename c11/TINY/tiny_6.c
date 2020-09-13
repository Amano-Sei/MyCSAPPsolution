/*************************************************************************
    > File Name: tiny.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月10日 星期四 22时06分36秒
 ************************************************************************/

#include "csapp.h"

void echo(int fd);

//起初理解错题意了...不过即使这样也还是很简单
//重点是后面理解各种header

int main(int argc, char **argv){
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    listenfd = Open_listenfd(argv[1]);
    while(1){
        clientlen = sizeof(clientaddr);
        connfd = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        Getnameinfo((struct sockaddr *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
        puts("====================OPENED====================");
        printf("Accepted connection from (%s:%s)\n", hostname, port);
        echo(connfd);
        Close(connfd);
        puts("====================CLOSED====================");
    }
}

void echo(int fd){
    char buf[MAXLINE];
    rio_t rio;
    int clen;
    Rio_readinitb(&rio, fd);
    printf("Request header:\n");
    while(clen = Rio_readlineb(&rio, buf, MAXLINE)){
        Rio_writen(fd, buf, clen);
        printf("%s", buf);
        if(strcmp(buf, "\r\n") == 0)
            return;
    }
}

