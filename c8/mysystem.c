/*************************************************************************
    > File Name: mysystem.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月14日 星期四 17时26分27秒
 ************************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

extern char **environ;

int mysystem(char *command){
    pid_t pid = fork();
    char csh[] = "/bin/sh";
    char cac[] = "-c";
    char *cargv[4] = { csh, cac, command, NULL };
    int status;

    if(pid < 0){
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(0);
    }
    if(pid == 0)
        if(execve(csh, cargv, environ) < 0){
            fprintf(stderr, "execve error: %s\n", strerror(errno));
            exit(0);
        }

    if(waitpid(pid, &status, 0) < 0){
        fprintf(stderr, "waitpid error: %s\n", strerror(errno));
        exit(0);
    }
    if(WIFEXITED(status))
        return WEXITSTATUS(status);
    return status;
    //看了dalao代码，如果WIFSIGNALED(status)返回WTERMSIG(status)
    //我对waitpid的默认行为还有点迷糊，文档中说的是只会等待terminated的child
    //但是child如果terminated的话是要么会exit要么被signal终止吗这点却不是很清楚
    //csapp这一章的描述感觉有着一带而过的感觉，后续应该需要看好多书和文档（（（
}

int main(){
    printf("1. return by %d\n\n", mysystem("ls /desu --color=always"));
    printf("2. return by %d\n", system("ls /desu --color=always"));
    return 0;
}

