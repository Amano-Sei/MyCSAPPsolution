#include <stdio.h>
#include "csapp.h"
#include "proxy.h"
#include "cache.h"

/* You won't lose style points for including this long line in your code */
static const char *user_agent_hdr = "User-Agent: Mozilla/5.0 (X11; Linux x86_64; rv:10.0.3) Gecko/20120305 Firefox/10.0.3\r\n";

int main(int argc, char **argv)
{
    int listenfd;
    sigset_t mask;
    client *clientp;
    pthread_t tmp;
    struct cbuf *cep;

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    
    Sigemptyset(&mask);
    Sigaddset(&mask, SIGPIPE);
    Sigprocmask(SIG_BLOCK, &mask, NULL);

    cep = Malloc(sizeof(struct cbuf));
    cbuf_init(cep);

    listenfd = Open_listenfd(argv[1]);
    while(1){
        clientp = Malloc(sizeof(client));
        clientp->clientlen = sizeof(struct sockaddr_storage);
        clientp->connfd = Accept(listenfd, (struct sockaddr *)&clientp->clientaddr, &clientp->clientlen);
        clientp->cep = cep;
        Pthread_create(&tmp, NULL, serv_thread, clientp);
    }

    return 0;
}

void doit(int connfd, struct cbuf *cep){
    char buf[MAXLINE+16];
    char host[MAXLINE], port[32];
    char method[MAXLINE], url[MAXLINE];
    //char version[MAXLINE];
    char uri[MAXLINE];
    rio_t rio;
    int clientfd;
    int ret;
    struct ccb *cbp;
    char *conp;

    Rio_readinitb(&rio, connfd);
    //get request header
    if(Rio_readlineb(&rio, buf, MAXLINE) == 0)
        return;
    printf("%lx>>>%s", pthread_self(), buf);
    sscanf(buf, "%s%s", method, url);
    //version is not important
    if(strcasecmp(method, "GET") && strcasecmp(method, "CONNECT")){
        e501(connfd, method);
        return;
    }

    P(&cep->readentry);
    P(&cep->rmutex);
    cep->readcnt++;
    if(cep->readcnt == 1)
        P(&cep->resource);
    V(&cep->rmutex);
    V(&cep->readentry);

    cbp = cbuf_get(cep, url);

    if(cbp != NULL){
        //其实我们的实现完全没必要读全所有的请求行。
        if(read_requesthdrs(&rio) >= 0){
            Rio_writen(connfd, cbp->content, cbp->csize);
            cbuf_update(cep, cbp);
        }
        P(&cep->rmutex);
        cep->readcnt--;
        if(cep->readcnt == 0)
            V(&cep->resource);
        V(&cep->rmutex);
    }else{
        P(&cep->rmutex);
        cep->readcnt--;
        if(cep->readcnt == 0)
            V(&cep->resource);
        V(&cep->rmutex);

        switch(parseurl(url, uri, host, port)){
            case -1:
                e501(connfd, url);
                return;
            default:
                break;
        }

        clientfd = open_clientfd(host, port);
        if(clientfd < 0){
            e504(connfd, url, host, port);
            return;
        }

        sprintf(buf, "GET %s HTTP/1.0\r\n", uri);
        if(!Rio_writen(clientfd, buf, strlen(buf))){
            e504(connfd, url, host, port);
            Close(clientfd);
            return;
        }

        if((ret = send_requesthdrs(&rio, connfd, clientfd, host)) < 0){
            if(ret != -2)
                e504(connfd, url, host, port);
            Close(clientfd);
            return;
        }

        if((conp = get_resource(connfd, clientfd, &ret)) != NULL){
            P(&cep->wmutex);
            cep->writecnt++;
            if(cep->writecnt == 1)
                P(&cep->readentry);
            V(&cep->wmutex);
            P(&cep->resource);
            cbuf_insert(cep, url, conp, ret);
            V(&cep->resource);
            P(&cep->wmutex);
            cep->writecnt--;
            if(cep->writecnt == 0)
                V(&cep->readentry);
            V(&cep->wmutex);
            free(conp);
        }
        Close(clientfd);
    }
}

int parseurl(char *url, char *uri, char *host, char *port){
    char *p;
    if(strncmp(url, "https://", 8) == 0)
        return -1;
    else if(strncmp(url, "http://", 7) == 0)
        url += 7;

    strcpy(host, url);

    if((p=strchr(host, '/')) != NULL){
        strcpy(uri, p);
        *p = '\0';
    }else
        strcpy(uri, "/");

    if((p=strchr(host, ':')) != NULL){
        *p++ = '\0';
        strcpy(port, p);
    }else
        strcpy(port, "80");

    return 0;
}

int send_requesthdrs(rio_t *rp, int connfd, int clientfd, char *host){
    char buf[MAXLINE];
    int hashost = 0;
    int n;
    while((n = Rio_readlineb(rp, buf, MAXLINE)) > 2){
        if(!hashost && strncmp(buf, "Host:", 5) == 0)
            hashost = 1;
        else if(strncmp(buf, "User-Agent:", 11) == 0)
            continue;
        else if(strncmp(buf, "Connection:", 11) == 0)
            continue;
        else if(strncmp(buf, "Proxy-Connection:", 17) == 0)
            continue;
        //本来这里是想设置个变量来避免每次都进行这么多比较的...但是没必要
        //而且还能避免发送重复请求行的情况
        if(Rio_writen(clientfd, buf, n) == 0)
            return -1;
    }
    if(n != 2 || strcmp(buf, "\r\n"))
        return -2;
    if(!hashost){
        sprintf(buf, "Host: %s\r\n", host);
        if(!Rio_writen(clientfd, buf, strlen(buf)))
            return -1;
    }
    if(!Rio_writen(clientfd, user_agent_hdr, 86))
        return -1;
    if(!Rio_writen(clientfd, "Connection: close\r\n", 19))
        return -1;
    if(!Rio_writen(clientfd, "Proxy-Connection: close\r\n", 25))
        return -1;
    if(!Rio_writen(clientfd, "\r\n", 2))
        return -1;
    return 0;
}

char *get_resource(int connfd, int clientfd, int *clen){
    int cinsize = MAX_OBJECT_SIZE;
    char *forcache = Malloc(MAX_OBJECT_SIZE);
    char *fcp = forcache;

    char buf[MAXLINE];
    rio_t rio;
    int len = -1;
    int n;
    int tmp;
    char *p;
    Rio_readinitb(&rio, clientfd);

    n = Rio_readlineb(&rio, buf, MAXLINE);
    if(n <= 2){
        free(forcache);
        return NULL;
    }
    p = buf;
    while(*p && *p != ' ')
        p++;
    if(*++p){
        tmp = atoi(p);
        if(tmp < 200 || tmp >= 300)
            cinsize = -1;
    }else
        cinsize = -1;
    if(Rio_writen(connfd, buf, n) == 0){
        free(forcache);
        return NULL;
    }
    if(n <= cinsize){
        memcpy(fcp, buf, n);
        fcp += n;
        cinsize -= n;
    }else
        cinsize = -1;

    while((n = Rio_readlineb(&rio, buf, MAXLINE)) > 2){
        if(strncmp(buf, "Content-Length:", 15) == 0)
            sscanf(buf, "Content-Length:%d", &len);
        if(!Rio_writen(connfd, buf, n)){
            free(forcache);
            return NULL;
        }
        if(n <= cinsize){
            memcpy(fcp, buf, n);
            fcp += n;
            cinsize -= n;
        }else
            cinsize = -1;
    }
    if(!Rio_writen(connfd, "\r\n", 2)){
        free(forcache);
        return NULL;
    }
    if(2 <= cinsize){
        memcpy(fcp, "\r\n", 2);
        fcp += 2;
        cinsize -= 2;
    }else
        cinsize = -1;
    if(len < 0){
        while((n = Rio_readnb(&rio, buf, MAXLINE)) != 0){
            if(!Rio_writen(connfd, buf, n)){
                free(forcache);
                return NULL;
            }
            if(n <= cinsize){
                memcpy(fcp, buf, n);
                fcp += n;
                cinsize -= n;
            }else
                cinsize = -1;
        }
        if(errno == EPIPE || errno == ECONNRESET)
            cinsize = -1;
    }else{
        while(len > 0){
            n = Rio_readnb(&rio, buf, MAXLINE<=len?MAXLINE:len);
            if(n == 0){
                free(forcache);
                return NULL;
            }
            len -= n;
            if(!Rio_writen(connfd, buf, n)){
                free(forcache);
                return NULL;
            }
            if(n <= cinsize){
                memcpy(fcp, buf, n);
                fcp += n;
                cinsize -= n;
            }else
                cinsize = -1;
        }
    }
    if(cinsize >= 0){
        *clen = fcp-forcache;
        return forcache;
    }else{
        free(forcache);
        return NULL;
    }
}

inline void e501(int connfd, char *cause){
    clienterror(connfd, cause, "501", "Not Implemented", "PP does not implement this method");
}

inline void e504(int connfd, char *url, char *host, char *port){
    fprintf(stderr, " > Couldn't send request header to %s:%s\n", host, port);
    clienterror(connfd, url, "504", "Gateway Timeout", "PP couldn't connect to the server");
}

void *serv_thread(void *vargp){
    Pthread_detach(pthread_self());
    //detach the thread to release resources automatically

    client *cp = vargp;
    Getnameinfo((struct sockaddr *)&cp->clientaddr, cp->clientlen, cp->hostname, 32, cp->port, 32, NI_NUMERICHOST|NI_NUMERICSERV);
    printf("%lx + Accepted connection from %s:%s\n", pthread_self(), cp->hostname, cp->port);

    doit(cp->connfd, cp->cep);
    Close(cp->connfd);

    printf("%lx - Disconnected from %s:%s\n", pthread_self(), cp->hostname, cp->port);
    free(cp);
    return NULL;
}

void clienterror(int connfd, char *cause, char *errnum,
        char *shortmsg, char *longmsg){
    char header[MAXLINE], body[MAXLINE];
    size_t bodylen;
    sprintf(body, "<html><head><title>PP error</title></head>"
                  "<body bgcolor=ffffff>\r\n"
                  "<p>%s: %s</p>\r\n"
                  "<p>%s: %s</p>\r\n"
                  "<hr>\r\n"
                  "<p><em>The PP proxy server</em></p>\r\n"
                  "</body></html>\r\n", errnum, shortmsg, longmsg, cause);
    sprintf(header, "HTTP/1.0 %s %s\r\n"
                    "Server: PP Proxy Server\r\n"
                    "Content-Type: text/html; charset=UTF-8\r\n"
                    "Content-Length: %lu\r\n"
                    "Connection: close\r\n\r\n", errnum, shortmsg, bodylen=strlen(body));
    if(!Rio_writen(connfd, header, strlen(header)))
        return;
    Rio_writen(connfd, body, bodylen);
}

int read_requesthdrs(rio_t *rp){
    char buf[MAXLINE];
    int n;
    while((n = Rio_readlineb(rp, buf, MAXLINE)) > 2);
    if(n != 2 || strcmp(buf, "\r\n"))
        return -1;
    return 0;
}

