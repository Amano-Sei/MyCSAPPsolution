/*************************************************************************
    > File Name: select.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月13日 星期日 23时48分38秒
 ************************************************************************/

#include "csapp.h"

void echo(int connfd, char *from);
void command(void);

int main(int argc, char **argv){
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    fd_set read_set, ready_set;

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]);

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);

    while(1){
        ready_set = read_set;
        Select(listenfd+1, &ready_set, NULL, NULL, NULL);
        if(FD_ISSET(STDIN_FILENO, &ready_set))
            command();
        if(FD_ISSET(listenfd, &ready_set)){
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            char *hosp = malloc(32);
            char *serp = malloc(32);
            Getnameinfo((struct sockaddr *)&clientaddr, clientlen, hosp, 32, serp, 32, NI_NUMERICHOST|NI_NUMERICSERV);
            strcat(hosp, ":");
            strcat(hosp, serp);
            free(serp);
            echo(connfd, hosp);
            free(hosp);
            Close(connfd);
        }
    }
}

void command(void){
    char buf[MAXLINE];
    if(!Fgets(buf, MAXLINE, stdin))
        exit(0);
    printf("=>%s<=", buf);
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

