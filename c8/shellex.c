/*************************************************************************
    > File Name: shellex.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月09日 星期六 16时31分38秒
 ************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#define MAXARGS 128
#define MAXLINE 8192

//终于一点点有在学系统的感觉了
//好好玩hhh
//不是拒绝使用csapp.h，而是想熟悉下错误处理，虽然实际上这些可能都是借助包装函数完成的
//但是我也想成为能自己写出所有东西的人

extern char **environ;

void eval(char *cmdline);
int parseline(char *bur, char **argv);
int builtin_command(char **argv);

int main(){
    char cmdline[MAXLINE];
    while(1){
        printf("> ");
        char *tptr = fgets(cmdline, MAXLINE, stdin);
        if(tptr == NULL && ferror(stdin)){
            fprintf(stderr, "fgets error\n");
            exit(0);
        }
        if(feof(stdin))
            exit(0);
        eval(cmdline);
    }
}

void eval(char *cmdline){
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    if(argv[0] == NULL)
        return;

    if(!builtin_command(argv)){
        pid = fork();
        if(pid < 0){
            fprintf(stderr, "fork error: %s\n", strerror(errno));
            exit(0);
        }
        if(pid == 0){
            if(execve(argv[0], argv, environ) < 0){
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }
        if(!bg){
            int status;
            if(waitpid(pid, &status, 0) < 0){
                fprintf(stderr, "waitfg: waitpid error: %s\n", strerror(errno));
                exit(0);
            }
        }else
            printf("%d %s", pid, cmdline);
    }
    return;
}

int builtin_command(char **argv){
    if(!strcmp(argv[0], "quit"))
        exit(0);
    if(!strcmp(argv[0], "&"))
        return 1;
    return 0;
}

int parseline(char *buf, char **argv){
    char *delim;
    int argc;
    int bg;
    
    buf[strlen(buf)-1] = ' ';
    while(*buf && (*buf == ' '))
        buf++;

    argc = 0;
    while((delim = strchr(buf, ' '))){
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim+1;
        while(*buf && (*buf == ' '))
            buf++;
    }
    argv[argc] = NULL;

    if(argc == 0)
        return 1;

    if((bg = (*argv[argc-1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}

