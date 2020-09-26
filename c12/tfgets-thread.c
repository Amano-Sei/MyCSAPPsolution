/*************************************************************************
    > File Name: tfgets-thread.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月23日 星期三 11时36分17秒
 ************************************************************************/

#include "csapp.h"

//我们新建两个子线程，一个用来设置时间上限，一个用来读入。

//这里看了手册，他并没有处理被回收的tid被再次使用然后被timer给cancel的问题。
//我自己也没有想到更好的实现，我想到保证安全的做法可能需要信号量保证一串操作不会和另一个操作交叉进行
//或者用另一个函数pthread_timedjoin_np

void *timer(void *vargp);
void *reader(void *vargp);

struct getsargs{
    char *s;
    int size;
    FILE *stream;
};

char *tfgets(char *s, int size, FILE *stream){
    struct getsargs args;
    pthread_t tid1, tid2;
    char *ret;

    args.s = s;
    args.size = size;
    args.stream = stream;
    pthread_create(&tid1, NULL, reader, &args);
    pthread_create(&tid2, NULL, timer, &tid1);
    pthread_join(tid1, (void **)&ret);
    //这里其实有个问题，tid1被回收后有可能再次被用，然后如果timer去cancel的话...
    if(ret == PTHREAD_CANCELED)
        ret = NULL;
    else
        pthread_cancel(tid2);
    pthread_join(tid2, NULL);
    return ret;
}

void *timer(void *vargp){
    pthread_t tid = *(pthread_t *)vargp;
    sleep(5);
    pthread_cancel(tid);
    return NULL;
}

void *reader(void *vargp){
    struct getsargs *p = vargp;
    return fgets(p->s, p->size, p->stream);
}

