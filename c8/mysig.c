/*************************************************************************
    > File Name: mysig.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月11日 星期一 19时15分38秒
 ************************************************************************/

#include "mysig.h"

sighandler_t Signal(int signum, sighandler_t handler){
    struct sigaction action, old_action;

    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    if(sigaction(signum, &action, &old_action) < 0){
        fprintf(stderr, "Signal error: %s\n", strerror(errno));
        exit(0);
    }
    
    return old_action.sa_handler;
}

int Sigemptyset(sigset_t *set){
    int ret = sigemptyset(set);
    if(ret < 0){
        perror("Sigemptyset error");
        exit(0);
    }
    return ret;
}

int Sigfillset(sigset_t *set){
    int ret = sigfillset(set);
    if(ret < 0){
        perror("Sigfillset error");
        exit(0);
    }
    return ret;
}

int Sigaddset(sigset_t *set, int signum){
    int ret = sigaddset(set, signum);
    if(ret < 0){
        perror("Sigaddset error");
        exit(0);
    }
    return ret;
}

int Sigdelset(sigset_t *set, int signum){
    int ret = sigdelset(set, signum);
    if(ret < 0){
        perror("Sigdelset error");
        exit(0);
    }
    return ret;
}

int Sigprocmask(int how, const sigset_t *set, sigset_t *oldset){
    int ret = sigprocmask(how, set, oldset);
    if(ret < 0){
        perror("Sigprocmask error");
        exit(0);
    }
    return ret;
}

