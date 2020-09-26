/*************************************************************************
    > File Name: pool.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月24日 星期四 17时55分08秒
 ************************************************************************/

#include "csapp.h"

typedef struct{
    int maxfd;

    fd_set read_set;
    fd_set ready_set;

    fd_set write_set;
    fd_set ready_write_set;

    int nready;
    int maxi;
    int clientfd[FD_SETSIZE];
    char clientfrom[FD_SETSIZE][32];
    char buf[FD_SETSIZE][MAXLINE];
    int buflen[FD_SETSIZE];

    void *srcp[FD_SETSIZE];
    int filesize[FD_SETSIZE];
    int csize[FD_SETSIZE];
}pool;

void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p, char *host, char *port);
void check_clients(pool *p);
int check_header(pool *p, int ci);
int getpostargs(pool *pp, int ci, char *cgiargs);

void add_write(pool *p, int ci, int srcfd, int filesize);

void doit(int fd);
int read_requesthdrs(rio_t *rp, char *cgiargs, int mcode);
int parse_uri(char *uri, char *filename, char *cgiargs, int mcode);
int serve_static(int fd, char *filename, int filesize, int mcode, int ci, pool *p);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs, int mcode);
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg, int mcode);
int endwith(const char *s1, const char *s2);

