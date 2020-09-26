/*************************************************************************
    > File Name: gethostbyname_ts.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月22日 星期二 22时36分18秒
 ************************************************************************/

#include <netdb.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>

sem_t mutex;

//说实话，这里除了深层复制，还要在出现问题时深层free
//感觉还是挺麻烦的。

void init(){
    if(sem_init(&mutex, 0, 1) == -1){
        fprintf(stderr, "sem_init error: %s\n", strerror(errno));
        exit(0);
    }
}

int P(sem_t *sem){
    if(sem_post(sem) < 0){
        fprintf(stderr, "P error: %s\n", strerror(errno));
        exit(0);
    }
    return 0;
}

int V(sem_t *sem){
    if(sem_post(sem) < 0){
        fprintf(stderr, "V error: %s\n", strerror(errno));
        exit(0);
    }
    return 0;
}

inline size_t getlistsize(char **list){
    if(list == NULL)
        return 0;
    register size_t sz = 0;
    while(list[sz++]);
    return sz;
}

int copystring(char **dst, char *src){
    int len = strlen(src);
    *dst = malloc(len);
    if(*dst == NULL)
        return -1;
    memcpy(*dst, src, len+1);
    return 0;
}

int copylist(char ***dst, char **src){
    int len = getlistsize(src);
    if(len == 0){
        *dst = NULL;
        return 0;
    }
    *dst = malloc(len*sizeof(char *));
    if(dst == NULL)
        return -1;
    for(int i = 0; i < len-1; i++)
        if(copystring(&(*dst)[i], src[i]))
            return -1;
    (*dst)[len-1] = NULL;
    return 0;
}

void clearlist(char **list){
    if(list == NULL)
        return;
    for(int i = 0; list[i]; i++)
        free(list[i]);
    free(list);
}

void deepclear(struct hostent *p){
    if(p == NULL)
        return;
    if(p->h_name)
        free(p->h_name);
    clearlist(p->h_aliases);
    clearlist(p->h_addr_list);
    free(p);
}

struct hostent *gethostbyname_ts(const char *name){
    struct hostent *ret, *neo = NULL;
    static pthread_once_t once_control = PTHREAD_ONCE_INIT;
    int len;
    pthread_once(&once_control, init);
    P(&mutex);
    ret = gethostbyname(name);
    if(ret == NULL)
        goto badp;
    neo = malloc(sizeof(struct hostent));
    if(neo == NULL)
        goto badp;
    neo->h_addrtype = ret->h_addrtype;
    neo->h_length = ret->h_length;
    neo->h_aliases = NULL;
    neo->h_addr_list = NULL;

    if(copystring(&neo->h_name, ret->h_name)){
        ret = NULL;
        goto badp;
    }

    if(copylist(&neo->h_aliases, ret->h_aliases)){
        ret = NULL;
        goto badp;
    }
    
    if(copylist(&neo->h_addr_list, ret->h_addr_list)){
        ret = NULL;
        goto badp;
    }

badp:
    if(ret == NULL){
        deepclear(neo);
        neo = NULL;
    }
    V(&mutex);
    return neo;
}

