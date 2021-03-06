/*************************************************************************
    > File Name: tiny.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月10日 星期四 22时06分36秒
 ************************************************************************/

#include "csapp.h"

void doit(int fd);
int read_requesthdrs(rio_t *rp, char *cgiargs, int mcode);
int parse_uri(char *uri, char *filename, char *cgiargs, int mcode);
void serve_static(int fd, char *filename, int filesize, int mcode);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs, int mcode);
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg, int mcode);
int endwith(const char *s1, const char *s2);

void sigchld_handler(int signum);

int main(int argc, char **argv){
    sigset_t mask;
    //因为我们的write和read都是可以重启的
    //所以应该不用屏蔽...
    int listenfd, connfd;
    char hostname[MAXLINE], port[MAXLINE];
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;

    Sigemptyset(&mask);
    Sigaddset(&mask, SIGPIPE);
    Sigprocmask(SIG_BLOCK, &mask, NULL);
    Signal(SIGCHLD, sigchld_handler);

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
        printf("Accepted connection from (%s, %s)\n", hostname, port);
        doit(connfd);
        Close(connfd);
        puts("====================CLOSED====================");
    }
}

void doit(int fd){
    int ret;
    struct stat sbuf;
    int is_static;
    int mcode = 0;
    char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    char buf[MAXLINE];
    rio_t rio;
    //放在函数里面着实巧妙，因为缓冲区在栈里面，所以return的时候就自动释放了

    Rio_readinitb(&rio, fd);
    if(!Rio_readlineb(&rio, buf, MAXLINE))
        return;

    printf("Request header:\n");
    printf("%s", buf);
    uri[0] = method[0] = version[0] = '\0';
    //简单的初始化
    //看似没有必要，但是如果有人恶意地传送空格请求行
    //并且method中有一个"GET"，就炸了（
    sscanf(buf, "%s%s%s", method, uri, version);
    if(strcasecmp(method, "GET") == 0)
        mcode = 1;
    else if(strcasecmp(method, "HEAD") == 0)
        mcode = 2;
    else if(strcasecmp(method, "POST") == 0)
        mcode = 3;
    else{
        clienterror(fd, method, "501", "Not implemented", "TINY does not implement this method", 1);
        return;
    }
    ret = read_requesthdrs(&rio, cgiargs, mcode);
    if(ret == -3)
        return;
    else if(ret == -2){
        clienterror(fd, method, "400", "Bad Request", "TINY doesn't understand", mcode);
        return;
    }else if(ret == -1){
        clienterror(fd, method, "501", "Not implemented", "TINY does not implement this method", mcode);
        return;
    }

    is_static = parse_uri(uri, filename, cgiargs, mcode);
    if(stat(filename, &sbuf) < 0){
        clienterror(fd, filename, "404", "Not found", "TINY couldn't find this file", mcode);
        return;
    }

    if(is_static){
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)){
            clienterror(fd, filename, "403", "Forbidden",
                        "TINY couldn't read the file", mcode);
            return;
        }
        serve_static(fd, filename, sbuf.st_size, mcode);
    }else{
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)){
            clienterror(fd, filename, "403", "Forbidden",
                        "TINY couldn't run the CGI program", mcode);
            return;
        }
        serve_dynamic(fd, filename, cgiargs, mcode);
    }
}

int read_requesthdrs(rio_t *rp, char *cgiargs, int mcode){
    char buf[MAXLINE];
    char boundary[MAXLINE];
    int tcode = -1;
    int clen = -1, tlen, tclen;
    char *p, *ep, *rep, *insp;
    if(mcode != 3){
        do{
            if(!Rio_readlineb(rp, buf, MAXLINE))
                return -3;
            //还是前面那个问题，如果这个时候连接断开，读到了eof
            //如果这个时候buf有东西，这里就会永远在死循环中输出buf
            printf("%s", buf);
            return 0;
        }while(strcmp(buf, "\r\n"));
        //可以看到示例的行为与do...while别无二致
        //所以我换成do...while了
    }else{
        cgiargs[0] = '\0';
        do{
            if(!Rio_readlineb(rp, buf, MAXLINE))
                return -3;
            if(!strncmp(buf, "Content-Type:", 13)){
                p = buf+13;
                while(*p == ' ')
                    p++;
                if(!strcmp(p, "application/x-www-form-urlencoded\r\n"))
                    tcode = 0;
                else if(!strncmp(p, "multipart/form-data;", 20)){
                    tcode = 1;
                    p += 20;
                    while(*p == ' ')
                        p++;
                    boundary[0] = '\0';
                    sscanf(p, "boundary=%s\r\n", boundary);
                }else if(!strcmp(p, "text/plain\r\n"))
                    tcode = 2;
                else
                    return -1;
            }else if(!strncmp(buf, "Content-Length:", 15))
                sscanf(buf, "Content-Length:%d", &clen);
            printf("%s", buf);
        }while(strcmp(buf, "\r\n"));
        if(tcode < 0 || clen > MAXLINE)
           return -1;
        if(clen < 0)
            return -2;
        if(clen == 0)
            return 0;
        switch(tcode){
            case 0:
                if(!Rio_readnb(rp, cgiargs, clen))
                    return -3;
                return 0;
            case 1:
                tclen = Rio_readnb(rp, buf, clen);
                if(tclen == 0)
                    return -3;
                else if(tclen != clen)
                    return -2;
                tclen = strlen(boundary);
                if(tclen == 0)
                    return -2;
                insp = cgiargs;
                p = strstr(buf, boundary);
                if(!p)
                    return -2;
                ep = p;
                while(1){
                    p = ep+tclen;
                    ep = strstr(p, boundary);
                    if(!ep){
                        if(insp != cgiargs)
                            *--insp = '\0';
                        return 0;
                    }
                    p = strchr(p, '\"');
                    if(!p || p > ep)
                        return -2;
                    rep = strchr(p+1, '\"');
                    if(!rep || rep > ep)
                        return -2;
                    strncpy(insp, p+1, rep-p-1);
                    insp += rep-p-1;
                    *insp++ = '=';
                    p = rep+5;
                    if(p > ep-4)
                        return -2;
                    strncpy(insp, p, ep-4-p);
                    insp += ep-4-p;
                    *insp++ = '&';
                }
            case 2:
                tclen = 0;
                while(clen > 0){
                    tlen = Rio_readlineb(rp, buf, MAXLINE);
                    if(tlen == 0)
                        return -3;
                    else if(tlen < 2)
                        return -2;
                    buf[tlen-2] = '&';
                    strncat(cgiargs, buf, tlen-1);
                    //本来想考虑下超长的情况的，但是还是算了...
                    clen -= tlen;
                    tclen += tlen-1;
                }
                if(clen)
                    return -2;
                cgiargs[tclen-1] = '\0';
                return 0;
        }
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

void serve_static(int fd, char *filename, int filesize, int mcode){
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
        return;
    printf("Response headers:\n%s", buf);
    if(mcode == 2)
        return;

    srcfd = Open(filename, O_RDONLY, 0);
    if(filesize <= MAXLINE*10){
        srcp = Malloc(filesize);
        Rio_readn(srcfd, srcp, filesize);
        Close(srcfd);

        Rio_writen(fd, srcp, filesize);
        free(srcp);
    }else{
        srcp = Mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
        Close(srcfd);
        Rio_writen(fd, srcp, filesize);
        Munmap(srcp, filesize);
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

void sigchld_handler(int signum){
    int old_errno = errno;
    int status;
    pid_t pid;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0){
        if(WIFEXITED(status)){
            printf("Cgi program %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        }else if(WIFSIGNALED(status)){
            printf("Cgi program %d terminated by signal: ", pid);
            psignal(WTERMSIG(status), NULL);
        }else{
            printf("pid %d returned by unknowed reason...\n", pid);
            exit(0);
        }
    }
    if(pid < 0 && errno != ECHILD)
        unix_error("sigchld_hanlder error");
    errno = old_errno;
    //这里是看别人之后加的，想了下确实有必要
}

