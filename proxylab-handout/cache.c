/*************************************************************************
    > File Name: cache.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月30日 星期三 09时28分06秒
 ************************************************************************/

#include "csapp.h"
#include "cache.h"

//调用gethash时需要保证url不是以http开头
static size_t gethash(char *url){
    size_t ret = 0;
    while(*url)
        ret = ((ret<<1) + *url++)%MAX_HASH;
    return ret;
}

//为了避免重复计算hash值，所以选择传入hash值
static struct ccb *getbyurlwithhash(struct cbuf *cp, char *url, size_t chash){
    register struct ccb *ret = cp->ht[chash];
    while(ret != NULL && strcmp(ret->url, url) != 0)
        ret = ret->hnxtp;
    return ret;
}

//调用时保证bp的csize已经被设置。
static void cbuf_insert_node(struct cbuf *cp, struct ccb *bp, size_t chash){
    cp->totsize += bp->csize;

    bp->nxtp = &cp->header;
    bp->prep = cp->header.prep;
    bp->nxtp->prep = bp;
    bp->prep->nxtp = bp;

    bp->hnxtp = cp->ht[chash];
    bp->hprep = NULL;
    cp->ht[chash] = bp;
    if(bp->hnxtp)
        bp->hnxtp->hprep = bp;
}

static void cbuf_delete_node(struct cbuf *cp, struct ccb *bp, size_t chash){
    cp->totsize -= bp->csize;

    bp->nxtp->prep = bp->prep;
    bp->prep->nxtp = bp->nxtp;

    if(bp->hnxtp)
        bp->hnxtp->hprep = bp->hprep;
    if(bp->hprep)
        bp->hprep->hnxtp = bp->hnxtp;
    else
        cp->ht[chash] = bp->hnxtp;
    free(bp->url);
    free(bp->content);
    free(bp);
}

void cbuf_init(struct cbuf *cp){
    Sem_init(&cp->readentry, 0, 1);
    Sem_init(&cp->rmutex, 0, 1);
    Sem_init(&cp->wmutex, 0, 1);
    Sem_init(&cp->resource, 0, 1);
    Sem_init(&cp->linkmutex, 0, 1);

    cp->readcnt = cp->writecnt = cp->totsize = 0;
    cp->header.url = cp->header.content = NULL;
    cp->header.csize = 0;
    cp->header.prep = cp->header.nxtp = &cp->header;

    memset(cp->ht, 0, sizeof(cp->ht));
}

void cbuf_deinit(struct cbuf *cp){
    struct ccb *hp = &cp->header;
    while(hp->nxtp != hp)
        cbuf_delete_node(cp, hp->nxtp, gethash(hp->nxtp->url));
}


void cbuf_insert(struct cbuf *cp, char *url, char *content, int clen){
    if(strncmp(url, "http://", 7) == 0)
        url += 7;
    size_t chash = gethash(url);
    struct ccb *ncb;
    size_t ulen = strlen(url);
    
    if(clen > MAX_OBJECT_SIZE)
        return;
    //其实没必要

    //P(&cp->linkmutex);
    //因为insert的操作已经从写者那里保证互斥了。

    ncb = getbyurlwithhash(cp, url, chash);
    if(ncb == NULL){
        ncb = Malloc(sizeof(struct ccb));

        ncb->url = Malloc(ulen+1);
        strcpy(ncb->url, url);

        ncb->content = Malloc(clen);
        memcpy(ncb->content, content, clen);

        ncb->csize = clen;

        while(cp->totsize+clen > MAX_CACHE_SIZE)
            cbuf_delete_node(cp, cp->header.nxtp, gethash(cp->header.nxtp->url));

        cbuf_insert_node(cp, ncb, chash);
    }

    //V(&cp->linkmutex);
}

void cbuf_update(struct cbuf *cp, struct ccb *bp){
    P(&cp->linkmutex);
    //一开始觉得这里省事可以用delete再insert
    //但是是不可以的，因为update有可能会和get同时出现
    //所以我们update时是不能动hash表的。

    bp->nxtp->prep = bp->prep;
    bp->prep->nxtp = bp->nxtp;

    bp->prep = cp->header.prep;
    bp->nxtp = &cp->header;
    bp->nxtp->prep = bp;
    bp->prep->nxtp = bp;

    V(&cp->linkmutex);
}

struct ccb *cbuf_get(struct cbuf *cp, char *url){
    if(strncmp(url, "http://", 7) == 0)
        url += 7;
    return getbyurlwithhash(cp, url, gethash(url));
}

