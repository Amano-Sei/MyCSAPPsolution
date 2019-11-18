/*************************************************************************
    > File Name: waitpid8_24.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月14日 星期四 20时43分51秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

#define N 4

int main(){
    int status, i;
    pid_t pid;
    int sig;
    for(i = 0; i < N; i++){
        pid = fork();
        if(pid < 0){
            perror("fork error");
            exit(EXIT_FAILURE);
        }
        if(pid == 0){
            if(i < 2)
                exit(100+i);
            else{
                //kill(getpid(), SIGSEGV);
                char *a = NULL;
                *a = 'a';
            }
        }
    }

    while((pid = waitpid(-1, &status, 0)) > 0){
        if(WIFEXITED(status))
            printf("child %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
        else if(WIFSIGNALED(status)){
            sig = WTERMSIG(status);
            fprintf(stderr, "child %d terminated by signal %d: ", pid, sig);
            psignal(sig, NULL);
            //其实这里在想是不是sprintf比较好，不过应该没必要吧（
            //大佬写了sprintf，所以我们也写一遍，但是放在注释里面（
            //而且psignal明显有用sprintf的意思
            //char buf[512];
            //sprintf(buf, "child %d terminated by signal %d", pid, sig);
            //psignal(sig, buf);
        }else
            fprintf(stderr, "child %d terminated abnormally\n", pid);
    }

    if(errno != ECHILD){
        perror("waitpid error");
        exit(0);
    }

    exit(0);
}

