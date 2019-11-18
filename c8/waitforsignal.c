/*************************************************************************
    > File Name: waitforsignal.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月11日 星期一 19时12分13秒
 ************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "mysig.h"

volatile sig_atomic_t pid;

void sigchld_handler(int s){
    int olderrno = errno;
    pid = waitpid(-1, NULL, 0);
    errno = olderrno;
}

void sigint_handler(int s){
}

int main(int argc, char **argv){
    sigset_t mask, prev;
    pid_t tpid;

    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGINT, sigint_handler);

    if(sigemptyset(&mask) < 0){
        fprintf(stderr, "sigemptyset error: %s\n", strerror(errno));
        exit(0);
    }

    if(sigaddset(&mask, SIGCHLD) < 0){
        fprintf(stderr, "sigaddset error: %s\n", strerror(errno));
        exit(0);
    }

    while(1){
        if(sigprocmask(SIG_BLOCK, &mask, &prev) < 0){
            fprintf(stderr, "sigprocmask error: %s\n", strerror(errno));
            exit(0);
        }
        tpid = fork();
        if(tpid < 0){
            fprintf(stderr, "fork error: %s\n", strerror(errno));
            exit(0);
        }
        if(tpid == 0)
            exit(0);
        pid = 0;
        if(sigprocmask(SIG_SETMASK, &prev, NULL) < 0){
            fprintf(stderr, "sigprocmask error: %s\n", strerror(errno));
            exit(0);
        }

        while(!pid)
            sleep(1);
            //pause();
        printf(".");
    }
    exit(0);
}

