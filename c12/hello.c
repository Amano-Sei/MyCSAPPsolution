/*************************************************************************
    > File Name: hello.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月17日 星期四 10时45分53秒
 ************************************************************************/
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void *thread(void *args);

int main(){
    int rt;
    pthread_t tid, stid = pthread_self();
    rt = pthread_create(&tid, NULL, thread, &stid);
    if(rt != 0){
        fprintf(stderr, "pthread_create error: %s\n", strerror(rt));
        exit(-1);
    }
    rt = pthread_join(tid, NULL);
    if(rt != 0){
        fprintf(stderr, "pthread_join error: %s\n", strerror(rt));
        exit(-1);
    }
    printf("1234567\n\n?");
    //exit(0);
    return 0;
}

void *thread(void *args){
    //printf("Hello world\n");
    //pthread_join(*(pthread_t *)args, NULL);
    //printf("here done...\n");
    int fd = open("outputdesu", O_CREAT|O_TRUNC|O_WRONLY, S_IRUSR);
    printf("%d %d\n", fd, STDOUT_FILENO);
    dup2(fd, 1);
    return NULL;
}

