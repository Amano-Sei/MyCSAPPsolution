/*************************************************************************
    > File Name: tsetenv.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月14日 星期四 17时07分42秒
 ************************************************************************/

#define _GNU_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char **argv){
    if(fork() == 0)
        execve("myecho", argv, environ);
    wait(NULL);
    printf("\n\n%d\n\n", setenv("mydefinedenvdesu", "desu", 0));
    if(fork() == 0)
        execve("myecho", argv, environ);
    fflush(stdout);
    wait(NULL);
    printf("\n\n%d\n\n", setenv("mydefinedenvdesu", "desud", 0));
    fflush(stdout);
    if(fork() == 0)
        execve("myecho", argv, environ);
    fflush(stdout);
    return 0;
}

