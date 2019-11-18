/*************************************************************************
    > File Name: signal1.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月10日 星期日 20时25分10秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mysio.h"

void handler1(int sig){
    int olderrno = errno;
    pid_t pid;
    if((pid = waitpid(-1, NULL, 0)) < 0)
        my_sio_error("waitpid error\n");
    my_sio_puts("Handler reaped the child ");
    my_sio_putl(pid);
    my_sio_puts("\n");
    if(sleep(1) < 0)
        my_sio_error("sleep error\n");
    errno = olderrno;
}

int main(){
    int i, n;
    char buf[8192];
    if(signal(SIGCHLD, handler1) == SIG_ERR){
        fprintf(stderr, "signal error: %s\n", strerror(errno));
        exit(0);
    }

    for(i = 0; i < 3; i++){
        pid_t pid = fork();
        if(pid < 0){
            fprintf(stderr, "fork error: %s\n", strerror(errno));
            exit(0);
        }
        if(pid == 0){
            printf("Hello from child %d\n", getpid());
            exit(0);
        }
    }

    if((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0){
        fprintf(stderr, "read error: %s\n", strerror(errno));
        exit(0);
    }
    printf("Parent processing input\n");
    while(1);

    exit(0);
}

