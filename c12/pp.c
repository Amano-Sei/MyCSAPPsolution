/*************************************************************************
    > File Name: proxy.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月26日 星期六 12时23分29秒
 ************************************************************************/

#include "./TINY/csapp.h"
#define LOGFILE "pplog"

void doit(int connfd);
void clienterror(int connfd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg);
int buf2fd(rio_t *rp, char *buf, int connfd);
void passlast(int connfd, int clientfd);

void clienterror(int connfd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg);

void *serv_thread(void *vargp);

sem_t mutex;
int logfd;

int main(int argc, char **argv){
    sigset_t mask;
    pthread_t tid;
    int listenfd, connfd;
    struct sockaddr_storage clientaddr;
    socklen_t clientlen;
    char clienthost[32], clientport[32];
    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    Sem_init(&mutex, 0, 1);

    Sigemptyset(&mask);
    Sigaddset(&mask, SIGPIPE);
    Sigprocmask(SIG_BLOCK, &mask, NULL);

    logfd = Open(LOGFILE, O_CREAT|O_APPEND|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);

    listenfd = Open_listenfd(argv[1]);
    while(1){
        clientlen = sizeof(struct sockaddr_storage);
        connfd = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
        //Getnameinfo((struct sockaddr *)&clientaddr, clientlen, clienthost, 32, clientport, 32, NI_NUMERICHOST|NI_NUMERICSERV);
        //printf(" > get connection from %s:%s\n", clienthost, clientport);
        Pthread_create(&tid, NULL, serv_thread, (void *)connfd);
        //printf(" > disconnected from %s:%s\n", clienthost, clientport);
    }
    return 0;
}

void doit(int connfd){
    char buf[MAXLINE];
    rio_t rio;
    int clientfd;

    Rio_readinitb(&rio, connfd);
    if(!Rio_readlineb(&rio, buf, MAXLINE))
        return;

    printf("Request Header:\n%s", buf);
    if((clientfd = buf2fd(&rio, buf, connfd)) < 0){
        clienterror(connfd, buf, "502", "Bad Gateway", "PP couldn't connect to the url");
        return;
    }
    passlast(connfd, clientfd);
    close(clientfd);
}

int buf2fd(rio_t *rp, char *buf, int connfd){
    char cbuf[MAXLINE];
    char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char port[32], host[MAXLINE/2], nuri[MAXLINE];;
    int clientfd;
    int n;

    char *p;
    method[0] = uri[0] = version[0] = '\0';
    sscanf(buf, "%s%s%s", method, uri, version);
    if(strncmp(uri, "/to?url=", 8)){
        while(Rio_readlineb(rp, cbuf, MAXLINE) > 2);
        clienterror(connfd, uri, "401", "Bad Request", "PP couldn't understand");
        return -1;
    }
    n = 8;
    P(&mutex);
    write(logfd, &uri[8], strlen(&uri[8]));
    write(logfd, "\n", 1);
    V(&mutex);
    if(strncmp(&uri[8], "http://", 7) == 0)
        n = 15;
    else if(strncmp(&uri[8], "https://", 8) == 0)
        n = 16;
    if(p = strchr(&uri[n], '/')){
        strcpy(nuri, p);
        *p = '\0';
    }else
        strcpy(nuri, "/");
    strcpy(host, &uri[n]);
    if(p = strchr(host, ':')){
        strcpy(port, p+1);
        *p = '\0';
    }else{
        if(n == 16)
            strcpy(port, "443");
        else
            strcpy(port, "80");
    }

    printf(" > %s %s %s\n", host, port, nuri);

    clientfd = Open_clientfd(host, port);
    if(clientfd < 0){
        while(Rio_readlineb(rp, cbuf, MAXLINE) > 2);
        clienterror(connfd, uri, "502", "Bad Gateway", "PP couldn't connect to the url");
        return -1;
    }
    sprintf(cbuf, "%s %s %s\r\n", method, nuri, version);
    if(!Rio_writen(clientfd, cbuf, strlen(cbuf))){
        Close(clientfd);
        while(Rio_readlineb(rp, cbuf, MAXLINE) > 2);
        clienterror(connfd, buf, "502", "Bad Gateway", "PP couldn't connect to the url");
        return -1;
    }
    printf(">>> %s", cbuf);
    while((n = Rio_readlineb(rp, cbuf, MAXLINE)) > 2){
        if(strncasecmp(cbuf, "Host:", 5) == 0){
            sprintf(cbuf, "Host: %s\r\n", host);
            n = strlen(cbuf);
        }
        printf(">>> %s", cbuf);
        if(Rio_writen(clientfd, cbuf, n) == 0){
            Close(clientfd);
            return -1;
        }
    }
    if(n != 2 || Rio_writen(clientfd, cbuf, 2) == 0){
        Close(clientfd);
        return -1;
    }

    return clientfd;
}

void passlast(int connfd, int clientfd){
    rio_t rio;
    char buf[MAXLINE];
    Rio_readinitb(&rio, clientfd);
    int n;
    int len = 0;
    while((n = Rio_readlineb(&rio, buf, MAXLINE)) > 2){
        printf("<<< %s", buf);
        if(strncasecmp(buf, "Content-length:", 15) == 0)
            sscanf(&buf[15], "%d", &len);
        if(Rio_writen(connfd, buf, n) == 0)
            return;
    }
    if(n != 2)
        return;
    Rio_writen(connfd, buf, 2);
    if(len > 0){
        while(len > 0){
            n = Rio_readlineb(&rio, buf, MAXLINE);
            printf("<<< %s", buf);
            if(n == 0)
                return;
            if(Rio_writen(connfd, buf, n) == 0)
                return;
            len -= n;
        }
    }else{
        while(n = Rio_readlineb(&rio, buf, MAXLINE)){
            printf("<<< %s", buf);
            if(Rio_writen(connfd, buf, n) == 0)
                return;
        }
    }
}

void clienterror(int connfd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg){
    char buf[MAXLINE], body[MAXLINE];
    size_t blen;
    sprintf(body, "<html><head><title>PP Error</title></head>"
                  "<body bgcolor=ffffff>\r\n"
                  "<p>%s: %s</p>\r\n"
                  "<p>%s: %s</p>\r\n"
                  "<hr><em>The PP Proxy Server</em></body></html>\r\n",
                  errnum, shortmsg, longmsg, cause);
    blen = strlen(body);
    sprintf(buf, "HTTP/1.0 %s %s\r\n"
                 "Server: PP Proxy Server\r\n"
                 "Connection: close\r\n"
                 "Content-type: text/html;charset=UTF-8\r\n"
                 "Content-length: %lu\r\n\r\n",
                 errnum, shortmsg, blen);
    if(!Rio_writen(connfd, buf, strlen(buf)))
        return;
    Rio_writen(connfd, body, blen);
}

void *serv_thread(void *vargp){
    Pthread_detach(pthread_self());
    int connfd = (int)vargp;
    doit(connfd);
    Close(connfd);
}

