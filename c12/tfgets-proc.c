/*************************************************************************
    > File Name: tfgets-proc.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月23日 星期三 10时56分39秒
 ************************************************************************/

#include "csapp.h"

//到这里我就想起来了，第8章有做过一个alarm的版本
//这里一开始懵掉了，看了dalao的做法
//毕竟除了alarm外我们可以通过子进程sleep来计时

//还是手册里写的好，我们子进程总会结束总要被回收的。

static sigjmp_buf tfgets_env;

static void sighandler_sigchld(int signum){
    Wait(NULL);
    siglongjmp(tfgets_env, 1);
}
static char *ret;

char *tfgets(char *s, int size, FILE *stream){
    pid_t pid;
    if((pid = Fork()) == 0){
        Sleep(5);
        exit(0);
    }
    ret = NULL;
    void (*oldhandler)(int) = Signal(SIGCHLD, sighandler_sigchld);
    if(sigsetjmp(tfgets_env, 1) == 0){
        ret = fgets(s, size, stream);
        Kill(pid, SIGKILL);
        pause();
    }
    Signal(SIGCHLD, oldhandler);
    return ret;
}

