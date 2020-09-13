/*************************************************************************
    > File Name: tiny.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月10日 星期四 22时06分36秒
 ************************************************************************/

#include "csapp.h"

void doit(int fd);
void read_requesthdrs(rio_t *rp);
int parse_uri(char *uri, char *filename, char *cgiargs);
void serve_static(int fd, char *filename, int filesize);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs);
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg);
int endwith(const char *s1, const char *s2);

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
        printf("Accepted connection from (%s, %s)\n", hostname, port);
        doit(connfd);
        Close(connfd);
        puts("====================CLOSED====================");
    }
}

void doit(int fd){
    struct stat sbuf;
    int is_static;
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
    if(strcasecmp(method, "GET")){
        clienterror(fd, method, "501", "Not implemented", "TINY does not implement this method");
        return;
    }
    read_requesthdrs(&rio);

    is_static = parse_uri(uri, filename, cgiargs);
    if(stat(filename, &sbuf) < 0){
        clienterror(fd, filename, "404", "Not found", "TINY couldn't find this file");
        return;
    }

    if(is_static){
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)){
            clienterror(fd, filename, "403", "Forbidden",
                        "TINY couldn't read the file");
            return;
        }
        serve_static(fd, filename, sbuf.st_size);
    }else{
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)){
            clienterror(fd, filename, "403", "Forbidden",
                        "TINY couldn't run the CGI program");
            return;
        }
        serve_dynamic(fd, filename, cgiargs);
    }
}

void read_requesthdrs(rio_t *rp){
    char buf[MAXLINE];

    do{
        if(!Rio_readlineb(rp, buf, MAXLINE))
            return;
        //还是前面那个问题，如果这个时候连接断开，读到了eof
        //如果这个时候buf有东西，这里就会永远在死循环中输出buf
        printf("%s", buf);
    }while(strcmp(buf, "\r\n"));
    //可以看到示例的行为与do...while别无二致
    //所以我换成do...while了
}

int parse_uri(char *uri, char *filename, char *cgiargs){
    if(!strstr(uri, "cgi-bin")){
        strcpy(filename, "web");
        strcat(filename, uri);
        strcpy(cgiargs, "");
        if(uri[strlen(uri)-1] == '/')
            strcat(filename, "home.html");
        return 1;
    }else{
        char *ptr = index(uri, '?');
        if(ptr){
            strcpy(cgiargs, ptr+1);
            *ptr = '\0';
        }else
            strcpy(cgiargs, "");
        strcpy(filename, "web");
        strcat(filename, uri);
        return 0;
    }
}

void serve_static(int fd, char *filename, int filesize){
    int srcfd;
    char *srcp, buf[MAXLINE], filetype[4096];
    //因为4096怎么也够filetype了，而如果用MAXLINE会导致WARNING...
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n"
                 "Server: TINY Web Server\r\n"
                 "Connection: close\r\n"
                 "Content-length: %d\r\n"
                 "Content-type: %s\r\n\r\n", filesize, filetype);
    Rio_writen(fd, buf, strlen(buf));
    printf("Response headers:\n%s", buf);
    srcfd = Open(filename, O_RDONLY, 0);
    srcp = Mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    Rio_writen(fd, srcp, filesize);
    Munmap(srcp, filesize);
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
    else
        strcpy(filetype, "text/plain;charset=UTF-8");
}

void serve_dynamic(int fd, char *filename, char *cgiargs){
    char buf[MAXLINE], *emptylist[] = {NULL};
    sprintf(buf, "HTTP/1.0 200 OK\r\n"
                 "Server: TINY Web Server\r\n");
    //这里差点顺手再来个\r\n...
    //但是正如书里所说，只有cgi程序才知道Content-length
    //所以要交给cgi程序来结束header
    Rio_writen(fd, buf, strlen(buf));

    if(Fork() == 0){
        setenv("QUERY_STRING", cgiargs, 1);
        Dup2(fd, STDOUT_FILENO);
        Execve(filename, emptylist, environ);
    }
    Wait(NULL);
}

void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg){
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
    Rio_writen(fd, buf, strlen(buf));
    Rio_writen(fd, body, strlen(body));
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

