/*************************************************************************
    > File Name: tiny.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月10日 星期四 22时06分36秒
 ************************************************************************/

#include "csapp.h"
#include "pool.h"

int main(int argc, char **argv){
    sigset_t mask;
    //因为我们的write和read都是可以重启的
    //所以应该不用屏蔽...
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    pool *cpool = Malloc(sizeof(pool));

    Sigemptyset(&mask);
    Sigaddset(&mask, SIGPIPE);
    Sigprocmask(SIG_BLOCK, &mask, NULL);

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(1);
    }
    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, cpool);

    while(1){
        cpool->ready_set = cpool->read_set;
        cpool->ready_write_set = cpool->write_set;
        cpool->nready = Select(cpool->maxfd+1, &cpool->ready_set, &cpool->ready_write_set, NULL, NULL);

        if(FD_ISSET(listenfd, &cpool->ready_set)){
            clientlen = sizeof(clientaddr);
            connfd = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            Getnameinfo((struct sockaddr *)&clientaddr, clientlen, hostname, MAXLINE, port, MAXLINE, 0);
            printf("Accepted connection from (%s, %s)\n", hostname, port);
            add_client(connfd, cpool, hostname, port);
        }

        check_clients(cpool);
    }
}

int parse_uri(char *uri, char *filename, char *cgiargs, int mcode){
    if(strncmp(uri, "/cgi-bin/", 9)){
        strcpy(filename, "web");
        strcat(filename, uri);
        strcpy(cgiargs, "");
        if(uri[strlen(uri)-1] == '/')
            strcat(filename, "home.html");
        return 1;
    }else{
        if(mcode != 3){
            char *ptr = index(uri, '?');
            if(ptr){
                strcpy(cgiargs, ptr+1);
                *ptr = '\0';
            }else
                strcpy(cgiargs, "");
        }
        strcpy(filename, "web");
        strcat(filename, uri);
        return 0;
    }
}

int serve_static(int fd, char *filename, int filesize, int mcode, int ci, pool *p){
    int srcfd;
    char buf[MAXLINE], filetype[4096];
    char *srcp;
    //因为4096怎么也够filetype了，而如果用MAXLINE会导致WARNING...
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n"
                 "Server: TINY Web Server\r\n"
                 "Connection: close\r\n"
                 "Content-length: %d\r\n"
                 "Content-type: %s\r\n\r\n", filesize, filetype);
    if(!Rio_writen(fd, buf, strlen(buf)))
        return 0;
    printf("Response headers:\n%s", buf);
    if(mcode == 2)
        return 0;

    srcfd = Open(filename, O_RDONLY, 0);
    if(filesize <= MAXLINE*10){
        srcp = Malloc(filesize);
        Rio_readn(srcfd, srcp, filesize);
        Close(srcfd);

        Rio_writen(fd, srcp, filesize);
        free(srcp);
        return 0;
    }else{
        add_write(p, ci, srcfd, filesize);
        return 1;
    }
}

void get_filetype(char *filename, char *filetype){
    if(endwith(filename, ".html"))
        strcpy(filetype, "text/html;charset=UTF-8");
    else if(endwith(filename, ".gif"))
        strcpy(filetype, "image/gif");
    else if(endwith(filename, ".png"))
        strcpy(filetype, "image/png");
    else if(endwith(filename, ".jpg"))
        strcpy(filetype, "image/jpeg");
    else if(endwith(filename, ".mp4"))
        strcpy(filetype, "video/mp4");
    else if(endwith(filename, ".mpg"))
        strcpy(filetype, "audio/mpeg");
    else if(endwith(filename, ".mpeg"))
        strcpy(filetype, "video/mpeg");
    else
        strcpy(filetype, "text/plain;charset=UTF-8");
}

void serve_dynamic(int fd, char *filename, char *cgiargs, int mcode){
    char buf[MAXLINE], *emptylist[] = {NULL};

    sprintf(buf, "HTTP/1.0 200 OK\r\n"
                 "Server: TINY Web Server\r\n");
    //这里差点顺手再来个\r\n...
    //但是正如书里所说，只有cgi程序才知道Content-length
    //所以要交给cgi程序来结束header
    if(!Rio_writen(fd, buf, strlen(buf)))
        return;

    if(Fork() == 0){
        switch(mcode){
            case 2:
                setenv("REQUEST_METHOD", "HEAD", 1);
                break;
            case 3:
                setenv("REQUEST_METHOD", "POST", 1);
                break;
            default:
                setenv("REQUEST_METHOD", "GET", 1);
                break;
        }
        setenv("QUERY_STRING", cgiargs, 1);
        Dup2(fd, STDOUT_FILENO);
        Execve(filename, emptylist, environ);
    }
    wait(NULL);
    //现在才意识到这才是原书想要的做法
}

void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg, int mcode){
    char buf[MAXLINE], body[MAXBUF];
    sprintf(body, "<html><title>TINY Error</title>"
                  "<body bgcolor=ffffff>\r\n"
                  "<p>%s: %s</p>\r\n"
                  "<p>%s: %s</p>\r\n"
                  "<hr><em>The TINY Web server</em></body></html>\r\n",
                  errnum, shortmsg, longmsg, cause);
    sprintf(buf, "HTTP/1.0 %s %s\r\n"
                 "Server: TINY Web Server\r\n"
                 "Connection: close\r\n"
                 "Content-type: text/html;charset=UTF-8\r\n"
                 "Content-length: %lu\r\n\r\n",
                 errnum, shortmsg, strlen(body));
    if(!Rio_writen(fd, buf, strlen(buf)))
        return;
    if(mcode == 2)
        return;
    if(!Rio_writen(fd, body, strlen(body)))
        return;
}

//check whether s1 end with s2
//return 1 when s1 end with s2, otherwise 0.
int endwith(const char *s1, const char *s2){
    register int s1len = strlen(s1);
    register int s2len = strlen(s2);
    if(s2len > s1len)
        return 0;
    return !strcmp(s1+s1len-s2len, s2);
}

