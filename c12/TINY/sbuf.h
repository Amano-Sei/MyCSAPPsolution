/*************************************************************************
    > File Name: sbuf.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月25日 星期五 16时18分04秒
 ************************************************************************/

#include "csapp.h"
#define MAXTHREAD 32
#define MINTHREAD 4

typedef struct{
    int *buf;
    int n;
    int front;
    int rear;
    sem_t mutex;
    sem_t slots;
    sem_t items;

    //sem_t pmutex;
    pthread_t tid[MAXTHREAD];
    sem_t threads[MAXTHREAD];
    int tcnt;
}sbuf_t;

void doit(int fd);
int read_requesthdrs(rio_t *rp, char *cgiargs, int mcode);
int parse_uri(char *uri, char *filename, char *cgiargs, int mcode);
void serve_static(int fd, char *filename, int filesize, int mcode);
void get_filetype(char *filename, char *filetype);
void serve_dynamic(int fd, char *filename, char *cgiargs, int mcode);
void clienterror(int fd, char *cause, char *errnum,
                 char *shortmsg, char *longmsg, int mcode);
int endwith(const char *s1, const char *s2);

void sbuf_init(sbuf_t *sp, int n);
void sbuf_deinit(sbuf_t *sp);
void sbuf_insert(sbuf_t *sp, int item);
void sbuf_remove(sbuf_t *sp, int tid);

void *serv_thread(void *vargp);
void *less_thread(void *vargp);
//void *more_thread(void *vargp);

