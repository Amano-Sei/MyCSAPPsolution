/*************************************************************************
    > File Name: hellobug.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月21日 星期一 16时36分36秒
 ************************************************************************/

#include "csapp.h"
void *thread(void *vargp);

int main(){
    pthread_t tid;
    Pthread_create(&tid, NULL, thread, NULL);
    Pthread_exit(NULL);
    //Pthread_cancel(Pthread_self());
}

void *thread(void *vargp){
    Sleep(1);
    printf("Hello, world!\n");
    return NULL;
}

