/*************************************************************************
    > File Name: tkill.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月09日 星期六 18时44分31秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t pid = fork();
    if(pid < 0){
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(0);
    }
    if(pid == 0){
        pause();
        printf("never to here...\n");
        exit(0);
    }
    if(kill(pid, SIGKILL) < 0){
        fprintf(stderr, "kill error: %s\n", strerror(errno));
        exit(0);
    }
    printf("I killed %d...\n", pid);
    if(waitpid(pid, NULL, 0) < 0){
        fprintf(stderr, "waitpid error: %s\n", strerror(errno));
        exit(0);
    }
    printf("And I took his corpse...\n");
    exit(0);
}

