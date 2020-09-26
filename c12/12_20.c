/*************************************************************************
    > File Name: 12_20.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月22日 星期二 14时19分43秒
 ************************************************************************/

#define N 10
sem_t mutex, w;

//因为说用一个计数信号量和一个互斥信号量，我只能猜想是想要这样的答案的
//不过如果信号量是先入先出的话确实是公平的

//参考维基百科中第三类读者写者问题的实现，确保了在信号量在block和release时是先入先出的情况下一定没有线程会陷入饥饿
//不管是这里还是那个实现的话如果不断有读者涌进来，然后读者又总是去唤醒读者，那么就永远都轮不到写者

//然而这个傻子写出死锁了...write在P的时候加上互斥是为了保证申请的资源如果被写者申请到，只能是同一个写者。
//但是在V的时候就没必要互斥了，而且如果强行互斥的话还会死锁（两个写者）

void init(){
    sem_init(&mutex, 0, 1);
    sem_init(&w, 0, N);
}

void *read(void *vargp){
    P(&w);
    /* READ */
    V(&w);

    return NULL;
}

void *write(void *vargp){
    P(&mutex);
    for(int i = 0; i < N; i++)
        P(&w);
    V(&mutex);
    /* WRITE */
    //P(&mutex);
    for(int i = 0; i < N; i++)
        V(&w);
    //V(&mutex);

    return NULL;
}

