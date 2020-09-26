/*************************************************************************
    > File Name: echoclient.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月09日 星期三 09时54分31秒
 ************************************************************************/

#include "csapp.h"

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

    clientfd = Open_clientfd(host, port);
    Rio_readinitb(&rio, clientfd);
    //while(Fgets(buf, MAXLINE, stdin) != NULL){
    //    //Rio_writen(clientfd, buf, strlen(buf)-1);
    //    //不记得自己当初为什么专门写一个不传换行符的做法了，在第12章的时候回看了眼
    //    //结果读不出来东西，仔细一看这里是不传换行符的
    //    Rio_writen(clientfd, buf, strlen(buf));
    //    Rio_readlineb(&rio, buf, MAXLINE);
    //    printf("-");
    //    Fputs(buf, stdout);
    //    printf("-");
    //}

    //Rio_writen(clientfd, "1\n2\n3\n4\n", 8);
    //Rio_readnb(&rio, buf, 8);
    //printf("=%s=\n", buf);
    //Close(clientfd);
    //exit(0);
    Rio_writen(clientfd, "1", 1);
    Rio_readnb(&rio, buf, 8);
    exit(0);
}

