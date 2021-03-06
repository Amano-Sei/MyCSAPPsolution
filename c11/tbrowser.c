/*************************************************************************
    > File Name: echoclient.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月09日 星期三 09时54分31秒
 ************************************************************************/

#include "csapp.h"

char buf[MAXLINE]; 
int main(int argc, char **argv){
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;
    if(argc != 3){
        fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
        exit(0);
    }

    host = argv[1];
    port = argv[2];
    sprintf(buf, "GET / HTTP/1.1\r\nHost: %s\r\nConnection: close\r\n\r\n", host);

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
    Rio_writen(clientfd, buf, strlen(buf));
    while(Rio_readlineb(&rio, buf, MAXLINE))
        Fputs(buf, stdout);
    Close(clientfd);
    exit(0);
}

