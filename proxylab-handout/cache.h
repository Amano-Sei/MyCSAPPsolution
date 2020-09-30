/*************************************************************************
    > File Name: cache.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月29日 星期二 23时41分27秒
 ************************************************************************/

#include "csapp.h"
/* Recommended max cache and object sizes */

#ifndef CACHE_H
#define CACHE_H
#define MAX_CACHE_SIZE 1049000
#define MAX_OBJECT_SIZE 102400

#define MAX_HASH 10003

struct ccb{
    char *url;
    char *content;
    struct ccb *nxtp, *prep;
    struct ccb *hnxtp, *hprep;
    size_t csize;
};
//Cache Control Block

struct cbuf{
    sem_t readentry, rmutex, wmutex, resource;
    int readcnt;
    int writecnt;

    sem_t linkmutex;
    struct ccb header;
    int totsize;
    struct ccb *ht[MAX_HASH];
};

void cbuf_init(struct cbuf *cp);
void cbuf_deinit(struct cbuf *cp);

void cbuf_insert(struct cbuf *cp, char *url, char *content, int clen);
void cbuf_update(struct cbuf *cp, struct ccb *bp);
struct ccb *cbuf_get(struct cbuf *cp, char *url);
#endif

