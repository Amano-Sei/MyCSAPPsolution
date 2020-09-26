/*************************************************************************
    > File Name: select.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月13日 星期日 23时48分38秒
 ************************************************************************/

#include "csapp.h"

//其实就是实现一遍echoservers.c
//因为自己写，所以就瞎写了...

struct Client{
    int nxt, pre;
    int connfd;
    char *clientname;
    rio_t rio;
}cli[FD_SETSIZE];
fd_set read_set, ready_set;

void init();
void echo(int connfd, char *from);
void command(void);
void addclient(int connfd, char *clientname);
void deleteclient(int ci);
void checkclient();

int main(int argc, char **argv){
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    int maxfd = 0;

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    maxfd = listenfd = Open_listenfd(argv[1]);
    init();

    FD_ZERO(&read_set);
    FD_SET(STDIN_FILENO, &read_set);
    FD_SET(listenfd, &read_set);

    while(1){
        ready_set = read_set;
        Select(maxfd+1, &ready_set, NULL, NULL, NULL);
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
            addclient(connfd, hosp);
            if(connfd > maxfd)
                maxfd = connfd;
        }
        checkclient();
    }
}

void init(){
    for(int i = 0; i < FD_SETSIZE; i++)
        cli[i].connfd = -1;
    cli[0].pre = cli[0].nxt = 0;
}

void command(void){
    char buf[MAXLINE];
    if(!Fgets(buf, MAXLINE, stdin))
        exit(0);
    printf("=>%s<=", buf);
    fflush(stdout);
}

void addclient(int connfd, char *clientname){
    printf("%s connected to server.\n", clientname);
    int ci = 1;
    while(cli[ci].connfd >= 0)
        ci++;
    if(cli[0].nxt == 0){
        cli[0].pre = ci;
        cli[0].nxt = ci;
        cli[ci].nxt = 0;
        cli[ci].pre = 0;
    }else{
        cli[ci].nxt = cli[0].nxt;
        cli[cli[0].nxt].pre = ci;
        cli[ci].pre = 0;
        cli[0].nxt = ci;
    }
    FD_SET(connfd, &read_set);
    cli[ci].connfd = connfd;
    cli[ci].clientname = clientname;
    Rio_readinitb(&cli[ci].rio, connfd);
}

void deleteclient(int ci){
    FD_CLR(cli[ci].connfd, &read_set);
    Close(cli[ci].connfd);
    free(cli[ci].clientname);
    cli[cli[ci].pre].nxt = cli[ci].nxt;
    cli[cli[ci].nxt].pre = cli[ci].pre;
    cli[ci].connfd = -1;
}

void checkclient(){
    size_t n;
    char buf[MAXLINE];
    for(int i = cli[0].nxt; i != 0; i = cli[i].nxt)
        if(FD_ISSET(cli[i].connfd, &ready_set)){
            n = Rio_readlineb(&cli[i].rio, buf, MAXLINE);
            if(n == 0){
                printf("%s disconnected from server.\n", cli[i].clientname);
                deleteclient(i);
            }else{
                printf("server received %lu bytes from %s: %s\n", n, cli[i].clientname, buf);
                Rio_writen(cli[i].connfd, buf, n);
            }
        }
}

