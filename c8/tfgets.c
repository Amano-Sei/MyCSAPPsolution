/*************************************************************************
    > File Name: tfgets.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月14日 星期四 20时59分31秒
 ************************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>
#include <setjmp.h>

#include "mysio.h"

sigjmp_buf tfgets_env;

sighandler_t Signal(int signum, sighandler_t handler){
    struct sigaction action, old_action;

    action.sa_handler = handler;
    action.sa_flags = SA_RESTART;
    if(sigemptyset(&action.sa_mask) < 0)
        my_sio_error("Signal error\n");

    if(sigaction(signum, &action, &old_action) < 0)
        my_sio_error("Signal error\n");

    return old_action.sa_handler;
}

void handler(int sig){
    siglongjmp(tfgets_env, 1);
}

char *tfgets(char *s, int size, FILE *stream){
    char *ret = NULL;

    //sigset_t mask, prev;
    //if(sigemptyset(&mask) < 0)
    //    my_sio_error("sigemtpyset error\n");
    //if(sigaddset(&mask, SIGALRM) < 0)
    //    my_sio_error("sigaddset error\n");
    //if(sigprocmask(SIG_BLOCK, &mask, &prev) < 0)
    //    my_sio_error("sigprocmask error\n");
    //其实这一部分我感觉意义不大，除非有人故意发SIGALRM会触发bug
    //而且如果收到了SIGALRM即使被阻塞也会等待不再阻塞的时机直接抢夺控制
    //想了想还是去掉吧

    sighandler_t oldhandler = Signal(SIGALRM, handler);

    if(!sigsetjmp(tfgets_env, 1)){
        alarm(5);
        //sigprocmask(SIG_SETMASK, &prev, NULL);
        ret = fgets(s, size, stream);
        alarm(0);
        //dalao这里没有取消alarm，所以专门测试了下不取消的情况下，alarm会怎样
        //而且dalao还没有恢复handler（emmm我是不是应该换份答案看...
        //其实想想dalao那样在重复调用时会有很混乱的运行顺序...
        //而且，在不恢复的情况下sleep到alarm的时候会回退到ret是NULL的时候...
        //好他喵混乱（（（

        //其实这里有一点，如果alarm发送在fgets返回后和取消alarm之间，还是会返回指向输入的指针
        //我觉得这是合理的，因为事实上是在5秒内完成了输入
    }
    //sigprocmask(SIG_SETMASK, &prev, NULL);
    //私以为，应该没有没有执行sigprocmask就跑出来的可能性
    Signal(SIGALRM, oldhandler);
    return ret;
}

int main(){
    char s[100];
    while(1){
        char *fg = tfgets(s, 100, stdin);
        sleep(5);
        printf("%p\n", fg);
        if(fg)
            puts(fg);
    }
    return 0;
}

