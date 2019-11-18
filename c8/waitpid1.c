/*************************************************************************
    > File Name: waitpid1.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月07日 星期四 14时40分08秒
 ************************************************************************/

#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#define N 2

int main(){
    int status, i;
    pid_t pid[N+1];
    pid_t retpid;
    for(i = 0; i < N; i++){
        pid[i] = fork();
        if(pid[i] < 0){
            fprintf(stderr, "fork error: %s\n", strerror(errno));
            exit(0);
        }else if(pid[i] == 0)
            return 100+i;
    }
    sleep(10);
    i = 0;
    while((retpid = waitpid(pid[i++], &status, 0)) > 0)
        if(WIFEXITED(status))
            printf("child %d with status %x terminated normally with exit status = %d\n", retpid, status, WEXITSTATUS(status));
        else
            printf("child %d terminated abnormally\n", retpid);
    
    printf("%d %d %d %d\n", i, pid[i-1], status, errno);

    //fprintf(stderr, "last: %s\n", strerror(errno));
    if(errno != ECHILD)
        fprintf(stderr, "waitpid error\n");
    exit(0);
}

