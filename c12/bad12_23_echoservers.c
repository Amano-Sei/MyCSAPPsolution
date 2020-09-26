/*************************************************************************
    > File Name: echoservers.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月16日 星期三 22时09分53秒
 ************************************************************************/

//写在最前面，这里是几乎废齐的代码
//根据题意，实现一个进程或线程版本的服务器即可。

#include "csapp.h"

//我认为这里如果还坚持使用io多路复用的话
//我能想到的只有alarm函数了...

//我猜测题意其实只是想让我们实现一遍线程或者进程版本的并发...
//题中说的很清楚让你写一个改进版，而不是让你改进12.8的版本
//那个就懒得再来一遍了

//不过还是尝试写一下alarm版本

//我们会发现read在被SIGALRM中断后并不会返回...
//所以只能选择用siglongjump冲了...
//但是每读一个字符都要调用一次设置返回点代价是不是有点太高了...
//算了不写了...

//算了写出来也没啥

//最后是在rio_read上做手脚，每次读之前保存状态然后超时返回，然后全部换成nio(new

//其实最符合题意的或许是连续地无缓存地读一个字符...

typedef struct{
    int maxfd;
    fd_set read_set;
    fd_set ready_set;
    int nready;
    int maxi;
    //其实这个里面有个问题，maxi和maxfd只会变大不会变小
    //不过不会出现错误
    int clientfd[FD_SETSIZE];
    char clientfrom[FD_SETSIZE][32];
    rio_t clientrio[FD_SETSIZE];
}pool;

int byte_cnt = 0;

sigjmp_buf bp;

void init_pool(int listenfd, pool *p);
void add_client(int connfd, pool *p, char *host, char *port);
void check_clients(pool *p);
static ssize_t nio_read(rio_t *rp, char *usrbuf, size_t n);
ssize_t nio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);
ssize_t Nio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen);

void sighandler_sigalrm(int signum){
    printf("Slow is bad, too bad...\n");
    siglongjmp(bp, 1);
}

int main(int argc, char **argv){
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    static pool pool;
    char host[32], port[32];

    if(argc != 2){
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    listenfd = Open_listenfd(argv[1]);
    init_pool(listenfd, &pool);

    while(1){
        pool.ready_set = pool.read_set;
        pool.nready = Select(pool.maxfd+1, &pool.ready_set, NULL, NULL, NULL);

        if(FD_ISSET(listenfd, &pool.ready_set)){
            clientlen = sizeof(struct sockaddr_storage);
            connfd = Accept(listenfd, (struct sockaddr *)&clientaddr, &clientlen);
            Getnameinfo((struct sockaddr *)&clientaddr, clientlen, host, 32, port, 32, NI_NUMERICHOST|NI_NUMERICSERV);
            add_client(connfd, &pool, host, port);
        }
        check_clients(&pool);
    }
}

void init_pool(int listenfd, pool *p){
    p->maxi = -1;
    for(int i = 0; i < FD_SETSIZE; i++)
        p->clientfd[i] = -1;
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool *p, char *host, char *port){
    int i;
    p->nready--;
    for(i = 0; i < FD_SETSIZE; i++)
        if(p->clientfd[i] < 0){
            p->clientfd[i] = connfd;
            Rio_readinitb(&p->clientrio[i], connfd);
            strcpy(p->clientfrom[i], host);
            strcat(p->clientfrom[i], ":");
            strcat(p->clientfrom[i], port);

            FD_SET(connfd, &p->read_set);

            if(connfd > p->maxfd)
                p->maxfd = connfd;
            if(i > p->maxi)
                p->maxi = i;
            break;
        }
    if(i == FD_SETSIZE)
        app_error("add_client error: Too many clients");
}

void check_clients(pool *p){
    int i, connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for(i = 0; i <= p->maxi && p->nready > 0; i++){
        connfd = p->clientfd[i];
        rio = p->clientrio[i];

        if(connfd > 0 && FD_ISSET(connfd, &p->ready_set)){
            p->nready--;
            if((n = Nio_readlineb(&rio, buf, MAXLINE)) != 0){
                byte_cnt += n;
                printf("Server received %d (%d total) bytes on fd %d from %s\n", n, byte_cnt, connfd, p->clientfrom[i]);
                Rio_writen(connfd, buf, n);
            }else{
                printf("Connection from %s on fd %d closed.\n", p->clientfrom[i], connfd);
                Close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[i] = -1;
            }
        }
    }
}

static ssize_t nio_read(rio_t *rp, char *usrbuf, size_t n){
    int cnt;

    handler_t *oldhandler =  Signal(SIGALRM, sighandler_sigalrm);
    while (rp->rio_cnt <= 0) {  /* Refill if buf is empty */
        if(sigsetjmp(bp, 0) != 0)   //因为signal mask没有变，所以无所谓0 1
            break;
        alarm(5);
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, 
                   sizeof(rp->rio_buf));
        alarm(0);
        if (rp->rio_cnt < 0) {
            if (errno != EINTR) /* Interrupted by sig handler return */
                return -1;
        }
        else if (rp->rio_cnt == 0)  /* EOF */
            return 0;
        else 
            rp->rio_bufptr = rp->rio_buf; /* Reset buffer ptr */
    }
    alarm(0);
    Signal(SIGALRM, oldhandler);

    /* Copy min(n, rp->rio_cnt) bytes from internal buf to user buf */
    cnt = n;          
    if (rp->rio_cnt < n)   
	cnt = rp->rio_cnt;
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}
ssize_t nio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) 
{
    int n, rc;
    char c, *bufp = usrbuf;

    for (n = 1; n < maxlen; n++) { 
        if ((rc = nio_read(rp, &c, 1)) == 1) {
	    *bufp++ = c;
	    if (c == '\n') {
                n++;
     		break;
            }
	} else if (rc == 0) {
	    if (n == 1)
		return 0; /* EOF, no data read */
	    else
		break;    /* EOF, some data was read */
	} else
	    return -1;	  /* Error */
    }
    *bufp = 0;
    return n-1;
}
ssize_t Nio_readlineb(rio_t *rp, void *usrbuf, size_t maxlen) 
{
    ssize_t rc;

    if ((rc = nio_readlineb(rp, usrbuf, maxlen)) < 0){
        if(errno == ECONNRESET || errno == EPIPE){
            fprintf(stderr, "Nio_readlineb error: %s\n", strerror(errno));
            return 0;
        }
        unix_error("Nio_readlineb error");
    }
    return rc;
} 
