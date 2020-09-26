/*************************************************************************
    > File Name: 12_19.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月21日 星期一 17时15分27秒
 ************************************************************************/

sem_t rmutex, wmutex, w;
int readcnt;
int writecnt;

//一直在看的DAD的答案并不符合题意，他的做法只是让在读者到来后的写者陷入死循环
//而在读者到来前已经在等待的写者还是有可能会被写者唤醒

//自己思考了蛮久也查了不少读者写者的资料，怎么也想不到一定能让写者唤醒读者的做法

//突然意识到自己为什么陷入了误区呢，为什么要靠readcnt来推迟写者呢...
//明明从第二个写者开始就不让他们往下走不好了...

//本来是这样想的，但是如何让他们继续往下走又变成了问题...

//所以最符合题意的只是简单地在w外面再套一个wmutex，保证在等待的写者只能申请wmutex，然后V(&w)唤醒的是一个等待的读者，但是总觉得这样哪里不对...
//其实这个自己一开始就有想到，但是因为觉得接下来V(&wmutex)还会唤醒写者进程，所以觉得哪里不对。
//但是这是因为自己对于PV操作理解不到位导致的误解
//在V操作唤醒的同时，信号量已经被赋予给了被唤醒的那个进程，就这样（

void init(){
    sem_init(&rmutex, 0, 1);
    sem_init(&wmutex, 0, 1);
    sem_init(&w, 0, 1);
    readcnt = 0;
}

void *read(void *vargp){
    P(&rmutex);
    readcnt++;
    if(readcnt == 1)
        P(&w);
    V(&rmutex);
    /* READ */
    P(&rmutex);
    readcnt--;
    if(readcnt == 0)
        V(&w);
    V(&rmutex);

    return NULL;
}

void *writer(void *vargp){
    P(&wmutex);
    P(&w);
    /* WRITE */
    V(&w);
    V(&wmutex);

    return NULL;
}

