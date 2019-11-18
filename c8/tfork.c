/*************************************************************************
    > File Name: tfork.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月07日 星期四 12时34分04秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

int x = 1;

int main(){
    int y = 1;
    pid_t pid;
    if((pid = fork()) < 0){
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(0);
    }
    if(pid == 0){
        for(int i = 0; i < 100; i++)
        printf("child?: x = %d, y = %d, with id %d %d %d\n", ++x, ++y, getpid(), getppid(), pid);
    }else{
        waitpid(0, NULL, 0);
        for(int i = 0; i < 100; i++)
        printf("parent?: x = %d, y = %d , with id %d %d %d\n", --x, --y, getpid(), getppid(), pid);
    }
    printf("%d====\n", getpid());
    if((pid = fork()) < 0){
        fprintf(stderr, "fork error: %s\n", strerror(errno));
        exit(0);
    }
    if(pid == 0){
        printf("child?: x = %d, y = %d, with id %d %d\n", ++x, ++y, getpid(), getppid());
    }else{
        printf("parent?: x = %d, y = %d , with id %d %d\n", --x, --y, getpid(), getppid());
    }
    exit(0);
}

