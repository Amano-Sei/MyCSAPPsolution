/*************************************************************************
    > File Name: 10_9.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月06日 星期日 14时01分21秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

extern char **environ;

//摆明了诱导你dup2

void unix_error(char *s){
    fprintf(stderr, "%s error: %s\n", s, strerror(errno));
    exit(0);
}

pid_t Fork(){
    register pid_t ret = fork();
    if(ret < 0)
        unix_error("fork");
    return ret;
}

int main(int argc, char **argv){
    if(Fork() == 0){
        dup2(0, 3);
        if(execve("fstatcheck", argv, environ) < 0)
            unix_error("execve");
    }
    if(wait(NULL) < 0)
        unix_error("wait");
    printf("done\n");
    return 0;
}

