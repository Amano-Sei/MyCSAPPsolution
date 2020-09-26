/*************************************************************************
    > File Name: 12_21.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月22日 星期二 18时13分15秒
 ************************************************************************/

//因为阅读过wiki，所以这里就直接用wiki里的实现来写了

//这里的话，因为当有读者在读时，从第一个写者到来后就会锁上读者的入口
//然后新来的读者就不能++readcnt，更不能进行读
//直到最后一个之前就在读的读者完成读后释放掉资源的信号量后，写者就可以进入临界区了
//同时如果有更多的写者，他们也不需要重复锁上读者的入口，直到最后一个写者完成他的写后释放掉读者入口的锁，读者才能开始他的后续动作

sem_t rmutex, wmutex;
sem_t resource, readentry;
int readcnt, writecnt;

void init(){
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    sem_init(&resource, 0, 1);
    sem_init(&readentry, 0, 1);
}

void *read(void *vargp){
    P(&readentry);
    P(&rmutex);
    readcnt++;
    if(readcnt == 1)
        P(&resource);
    V(&rmutex);
    V(&readentry);
    /* READ */
    P(&rmutex);
    readcnt--;
    if(readcnt == 0)
        V(&resource);
    V(&rmutex);

    return NULL;
}

void *write(void *vargp){
    P(&wmutex);
    writecnt++;
    if(writecnt == 1)
        P(&readentry);
    V(&wmutex);
    
    P(&resource);
    /* WRITE */
    V(&resource);

    P(&wmutex);
    writecnt--;
    if(writecnt == 0)
        V(&readentry);
    V(&wmutex);
    return NULL;
}

