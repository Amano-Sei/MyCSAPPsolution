/*************************************************************************
    > File Name: pool.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月24日 星期四 16时46分29秒
 ************************************************************************/

#include "pool.h"
#include "csapp.h"

void init_pool(int listenfd, pool *p){
    p->maxi = -1;
    for(int i = 0; i < FD_SETSIZE; i++)
        p->clientfd[i] = -1;
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);

    FD_ZERO(&p->write_set);
}

void add_client(int connfd, pool *p, char *host, char *port){
    int i ;
    p->nready--;
    for(i = 0; i < FD_SETSIZE; i++)
        if(p->clientfd[i] < 0){
            p->clientfd[i] = connfd;
            strcpy(p->clientfrom[i], host);
            strcat(p->clientfrom[i], ":");
            strcat(p->clientfrom[i], port);

            FD_SET(connfd, &p->read_set);

            p->buflen[i] = 0;

            if(connfd > p->maxfd)
                p->maxfd = connfd;
            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    if(i == FD_SETSIZE)
        app_error("add_client error: Too many clients");
}

void check_clients(pool *p){
    int i, connfd, n;
    char buf[MAXLINE];
    for(i = 0; i <= p->maxi && p->nready > 0; i++){
        connfd = p->clientfd[i];
        if(connfd > 0){
            if(FD_ISSET(connfd, &p->ready_set)){
                p->nready--;
                if((n = Rio_readline(connfd, buf, MAXLINE)) <= 2){
                    FD_CLR(connfd, &p->read_set);
                    if(n == 2 && check_header(p, i) == 0 || n < 2){
                        printf("Connection from %s on fd %d closed.\n", p->clientfrom[i], connfd);
                        Close(connfd);
                        p->clientfd[i] = -1;
                    }
                }else{
                    if(p->buflen[i]+n >= MAXLINE){
                        p->buflen[i] = -1;
                        check_header(p, i);
                        printf("Connection from %s on fd %d closed.\n", p->clientfrom[i], connfd);
                        Close(connfd);
                        p->clientfd[i] = -1;
                        FD_CLR(connfd, &p->read_set);
                    }else{
                        strcpy(&p->buf[i][p->buflen[i]], buf);
                        p->buflen[i] += n;
                    }
                }
            }else if(FD_ISSET(connfd, &p->ready_write_set)){
                p->nready--;
                register int nsize = MAXLINE*10;
                if(p->filesize[i]-p->csize[i] <= nsize){
                    nsize = p->filesize[i]-p->csize[i];
                    Rio_writen(connfd, p->srcp[i]+p->csize[i], nsize);
                    Munmap(p->srcp[i], p->filesize[i]);
                    FD_CLR(connfd, &p->write_set);
                    printf("Connection from %s on fd %d closed.\n", p->clientfrom[i], connfd);
                    Close(connfd);
                    p->clientfd[i] = -1;
                }else{
                    if(Rio_writen(connfd, p->srcp[i]+p->csize[i], nsize) == 0){
                        Munmap(p->srcp[i], p->filesize[i]);
                        FD_CLR(connfd, &p->write_set);
                        printf("Connection from %s on fd %d closed.\n", p->clientfrom[i], connfd);
                        Close(connfd);
                        p->clientfd[i] = -1;
                    }
                    p->csize[i] += nsize;
                }
            }
        }
    }
}

int check_header(pool *p, int ci){
    int ret;
    struct stat sbuf;
    int is_static;
    int mcode = 0;
    char method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgiargs[MAXLINE];
    char buf[MAXLINE];
    int fd = p->clientfd[ci];

    printf("Request header:\n");
    printf("%s", p->buf[ci]);
    
    if(p->buflen[ci] < 0){
        clienterror(fd, "TINY CAN'T UNDERSTAND", "501", "Not implemented", "Too long header for TINY", 1);
        return 0;
    }

    uri[0] = method[0] = version[0] = '\0';

    sscanf(p->buf[ci], "%s%s%s", method, uri, version);
    if(strcasecmp(method, "GET") == 0)
        mcode = 1;
    else if(strcasecmp(method, "HEAD") == 0)
        mcode = 2;
    else if(strcasecmp(method, "POST") == 0)
        mcode = 3;
    else{
        clienterror(fd, method, "501", "Not implemented", "TINY does not implement this method", 1);
        return 0;
    }

    if(mcode == 3)
        ret = getpostargs(p, ci, cgiargs);
    if(ret == -3)
        return 0;
    else if(ret == -2){
        clienterror(fd, method, "400", "Bad Request", "TINY doesn't understand", mcode);
        return 0;
    }else if(ret == -1){
        clienterror(fd, method, "501", "Not implemented", "TINY does not implement this method", mcode);
        return 0;
    }

    is_static = parse_uri(uri, filename, cgiargs, mcode);
    if(stat(filename, &sbuf) < 0){
        clienterror(fd, filename, "404", "Not found", "TINY couldn't find this file", mcode);
        return 0;
    }

    if(is_static){
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IRUSR & sbuf.st_mode)){
            clienterror(fd, filename, "403", "Forbidden",
                        "TINY couldn't read the file", mcode);
            return 0;
        }
        return serve_static(fd, filename, sbuf.st_size, mcode, ci, p);
    }else{
        if(!(S_ISREG(sbuf.st_mode)) || !(S_IXUSR & sbuf.st_mode)){
            clienterror(fd, filename, "403", "Forbidden",
                        "TINY couldn't run the CGI program", mcode);
            return 0;
        }
        serve_dynamic(fd, filename, cgiargs, mcode);
        return 0;
    }
}

int getpostargs(pool *pp, int ci, char *cgiargs){
    char buf[MAXLINE];
    char boundary[MAXLINE];
    int tcode = -1;
    int clen = -1, tlen, tclen;
    char *p, *ep, *rep, *insp;
    int fd = pp->clientfd[ci];

    p = strstr(pp->buf[ci], "Content-Type:");
    if(p == NULL)
        return -1;
    p += 13;
    while(*p == ' ')
        p++;
    if(!strncmp(p, "application/x-www-form-urlencoded\r\n", 35))
        tcode = 0;
    else if(!strncmp(p, "multipart/form-data;", 20)){
        tcode = 1;
        p += 20;
        while(*p == ' ')
            p++;
        boundary[0] = '\0';
        sscanf(p, "boundary=%s\r\n", boundary);
    }else if(!strncmp(p, "text/plain\r\n", 12))
        tcode = 2;
    else
        return -1;

    p = strstr(pp->buf[ci], "Content-Length:");
    if(p != NULL){
        p += 15;
        sscanf(p, "%d", &clen);
    }else
        return -2;
    if(clen < 0)
        return -2;
    if(clen == 0)
        return 0;

    switch(tcode){
        case 0:
            if(!Rio_readn(fd, cgiargs, clen))
                return -3;
            cgiargs[clen] = '\0';
            return 0;
        case 1:
            tclen = Rio_readn(fd, buf, clen);
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
                tlen = Rio_readline(fd, buf, MAXLINE);
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

void add_write(pool *p, int ci, int srcfd, int filesize){
    p->srcp[ci] = Mmap(NULL, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    Close(srcfd);
    p->filesize[ci] = filesize;
    p->csize[ci] = 0;
    FD_SET(p->clientfd[ci], &p->write_set);
}

