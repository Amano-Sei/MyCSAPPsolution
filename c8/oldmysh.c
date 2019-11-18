/*************************************************************************
    > File Name: mysh.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月17日 星期六 15时01分09秒
 ************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

#include "mysio.h"
#include "mysig.h"

#define MAXARGS 128
#define MAXLINE 8192

//因为说在那个基础上来做，所以直接复制过来了

extern char **environ;

struct Proc{
    char *cmdline;
    int pid;
    int stat;
}proc[MAXARGS];
volatile sig_atomic_t tot = 0;
volatile sig_atomic_t cjid = 0;

void eval(char *cmdline, sigset_t *prev);
int parseline(char *bur, char **argv);
int builtin_command(char **argv);

void sigchld_handler(int signum);
void kill_handler(int signum);

pid_t builtin_kill(char *cid, int signum);
void builtin_jobs(char **argv);
int builtin_bg(char **argv);
void builtin_fg(char **argv);

int main(){
    sigset_t mask, prev;
    char cmdlines[MAXARGS+1][MAXLINE];
    int ci;
    Sigemptyset(&mask);
    Sigaddset(&mask, SIGCHLD);
    Sigprocmask(SIG_BLOCK, &mask, &prev);
    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGINT, kill_handler);
    Signal(SIGTSTP, kill_handler);

    while(1){
        Sigprocmask(SIG_SETMASK, &prev, NULL);
        Sigprocmask(SIG_BLOCK, &mask, NULL);

        for(ci = 0; ci < MAXARGS && cmdlines[ci][0]; ci++);
        printf("mysh > ");
        char *tptr = fgets(cmdlines[ci], MAXLINE, stdin);
        if(tptr == NULL && ferror(stdin)){
            fprintf(stderr, "fgets error\n");
            exit(0);
        }
        if(feof(stdin))
            exit(0);
        eval(cmdlines[ci], &prev);
    }
}

void eval(char *cmdline, sigset_t *prev){
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);

    if(argv[0] == NULL)
        return;

    if(!builtin_command(argv)){
        if(tot < MAXARGS){
            pid = fork();
            if(pid < 0){
                perror("fork error");
                exit(0);
            }
            if(pid == 0){
                Sigprocmask(SIG_SETMASK, prev, NULL);
                //execve貌似不会带走父进程的handler设置
                //但是block还是会带走的
                if(execve(argv[0], argv, environ) < 0){
                    printf("%s: Command not found.\n", argv[0]);
                    exit(0);
                }
            }
            proc[tot].pid = pid;
            proc[tot].stat = 1;
            proc[tot++].cmdline = cmdline;
            if(!bg){
                cjid = tot;
                int status;
                if(waitpid(pid, &status, WUNTRACED) < 0){
                    perror("waitfg: waitpid error");
                    exit(0);
                }

                if(WIFEXITED(status)){
                    printf("Job %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
                    proc[--tot].stat = 0;
                    proc[tot].cmdline[0] = '\0';
                    cjid = 0;
                }else if(WIFSIGNALED(status)){
                    fprintf(stderr, "Job %d terminated by signal: ", pid);
                    psignal(WTERMSIG(status), NULL);
                    proc[--tot].stat = 0;
                    proc[tot].cmdline[0] = '\0';
                    cjid = 0;
                }else if(WIFSTOPPED(status)){
                    fprintf(stderr, "Job %d stopped by signal: ", pid);
                    psignal(WSTOPSIG(status), NULL);
                    proc[tot-1].stat = 2;
                }else{
                    fprintf(stderr, "waitpid: unknowed return reason\n");
                    exit(0);
                }
            }else
                printf("[%d] %d %s", tot, pid, cmdline);
        }else{
            fprintf(stderr, "mysh: mysh can not have more than %d subprocesses.\n", MAXARGS);
        }
    }
    return;
}

int builtin_command(char **argv){
    if(!strcmp(argv[0], "quit"))
        exit(0);
    if(!strcmp(argv[0], "&"))
        return 1;
    if(!strcmp(argv[0], "jobs")){
        builtin_jobs(argv);
        return 1;
    }
    if(!strcmp(argv[0], "bg")){
        builtin_bg(argv);
        return 1;
    }
    if(!strcmp(argv[0], "fg")){
        builtin_fg(argv);
        return 1;
    }
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

void sigchld_handler(int signum){
    int status;
    int ci;
    pid_t pid;
    while((pid=waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0){
        for(ci = 0; ci < tot && proc[ci].pid != pid; ci++);
        if(ci == tot){
            fprintf(stderr, "no such job %d, but received such pid\n", pid);
            exit(0);
        }
        if(WIFEXITED(status)){
            printf("Job %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
            proc[ci].stat = 0;
            proc[ci].cmdline[0] = '\0';
        }else if(WIFSIGNALED(status)){
            fprintf(stderr, "Job %d terminated by signal: ", pid);
            psignal(WTERMSIG(status), NULL);
            proc[ci].stat = 0;
            proc[ci].cmdline[0] = '\0';
        }else if(WIFSTOPPED(status)){
            fprintf(stderr, "Job %d stopped by signal: ", pid);
            psignal(WSTOPSIG(status), NULL);
            proc[ci].stat = 2;
        }else{
            fprintf(stderr, "pid %d returned for unknowed reason...\n", pid);
            exit(0);
        }
        if(proc[ci].stat == 0){
            for(int i = ci; i < tot; i++){
                proc[i].pid = proc[i+1].pid;
                proc[i].cmdline = proc[i+1].cmdline;
                proc[i].stat = proc[i+1].stat;
            }
            tot--;
        }
    }
}

void kill_handler(int signum){
    if(cjid != 0){
        if(kill(proc[cjid-1].pid, signum) < 0){
            perror("kill error");
            exit(0);
        }
        putchar('\n');
    }else
        printf("\nmysh > ");
}

pid_t builtin_kill(char *cid, int signum){
    pid_t pid;
    if(cid != NULL){
        if(cid[0] == '%'){
            //jid
            pid = atoi(cid+1);
            if(pid <= 0 || pid > tot)
                //错误的jid范围
                return -1;
            pid = proc[pid-1].pid;
        }else
            pid = atoi(cid);
        if(pid <= 0)
            return -1;
        if(kill(pid, signum) < 0){
            if(errno == ESRCH)
                return -1;
            else if(errno == EPERM){
                return -3;
            }
            perror("fg/bg");
            exit(0);
        }
        return pid;
    }else
        return -2;
}

void builtin_jobs(){
    //本意是想存储更少的信息，然而现实是我不知道怎么做到不保存stat位做
    //一开始还头疼了下jobs要怎么写，然而只有waitpid才能做到，而且只能在被改变状态的时候知道他被改变了
    //所以下面的old的写法什么都不是（
    for(int i = 0; i < tot; i++)
        if(proc[i].stat == 1)
            printf("[%d] %d Running    %s", i+1, proc[i].pid, proc[i].cmdline);
        else if(proc[i].stat == 2)
            printf("[%d] %d Stopped    %s", i+1, proc[i].pid, proc[i].cmdline);
        else{
            fprintf(stderr, "unkowned job: [%d] %d %s", i+1, proc[i].pid, proc[i].cmdline);
            exit(0);
        }
}

void builtin_oldjobs(char **argv){
    int status, i;
    for(i = 0; i < tot; i++){
        pid_t pid = waitpid(proc[i].pid, &status, WNOHANG | WUNTRACED);
        if(pid > 0){
            if(WIFEXITED(status) || WIFSIGNALED(status)){
                //起初以为源码有锅，然而人家源码的括号加的好好的（
                //是我自己菜了
                printf("[%d] %d Terminated %s", i+1, proc[i].pid, proc[i].cmdline);
                proc[i].cmdline[0] = '\0';
                proc[i].cmdline[1] = status&0xff;
                proc[i].cmdline[2] = (status>>8)&0xff;
                proc[i].cmdline[3] = (status>>16)&0xff;
                proc[i].cmdline[4] = (status>>24)&0xff;
            }else if(WIFSTOPPED(status)){
                printf("[%d] %d Stopped    %s", i+1, proc[i].pid, proc[i].cmdline);
            }
        }else{
            if(WIFSTOPPED(status))
                printf("[%d] %d Stopped    %s", i+1, proc[i].pid, proc[i].cmdline);
            else
                printf("[%d] %d Running    %s", i+1, proc[i].pid, proc[i].cmdline);
        }
    }
    int j;
    for(i = 0, j = 0; i < tot; i++){
        if(proc[i].cmdline[0] == '\0'){
            int status = proc[i].cmdline[4];
            for(int k = 3; k > 1; k--)
                status = (status<<8)|proc[i].cmdline[k];
            if(WIFEXITED(status))
                printf("Job %d terminated normally with exit status=%d\n", proc[i].pid, WEXITSTATUS(status));
            else{
                fprintf(stderr, "Job %d terminated by signal: ", proc[i].pid);
                psignal(WTERMSIG(status), NULL);
            }
        }else{
            if(i != j){
                proc[j].pid = proc[i].pid;
                proc[j].cmdline = proc[i].cmdline;
            }
            j++;
        }
    }
    tot = j;
}

int builtin_bg(char **argv){
    pid_t pid = builtin_kill(argv[1], SIGCONT);
    if(pid > 0){
        for(int i = 0; i < tot; i++)
            if(proc[i].pid == pid){
                printf("[%d] %d %s", i+1, pid, proc[i].cmdline);
                return i+1;
            }
        printf("%s: No such process in job list, but it still continue\n", argv[1]);
        return 0;
    }else if(pid == -2){
        fprintf(stderr, "fg/bg: need avaliable pid or jid like 12345 or %%1\n");
    }else if(pid == -1){
        printf("%s: No such process\n", argv[1]);
    }else if(pid == -3){
        fprintf(stderr, "fg/bg: no permission to do this...\n");
    }
    return pid;
}

void builtin_fg(char **argv){
    int jid = builtin_bg(argv);
    int status;
    if(jid > 0){
        cjid = jid;
        if(waitpid(proc[jid-1].pid, &status, WUNTRACED) < 0){
            if(errno != EINTR){
                perror("waitfg: waitpid error");
                exit(0);
            }
        }else{
            if(WIFEXITED(status)){
                printf("Job %d terminated normally with exit status=%d\n", proc[jid-1].pid, WEXITSTATUS(status));
                proc[cjid-1].cmdline[0] = '\0';
                for(int i = jid; i < tot; i++){
                    proc[i-1].pid = proc[i].pid;
                    proc[i-1].cmdline = proc[i].cmdline;
                }
                tot--;
            }else if(WIFSIGNALED(status)){
                fprintf(stderr, "Job %d terminated by signal: ", proc[jid-1].pid);
                psignal(WTERMSIG(status), NULL);
                proc[cjid-1].cmdline[0] = '\0';
                for(int i = jid; i < tot; i++){
                    proc[i-1].pid = proc[i].pid;
                    proc[i-1].cmdline = proc[i].cmdline;
                }
                tot--;
            }else if(WIFSTOPPED(status)){
                fprintf(stderr, "Job %d stopped by signal: ", proc[jid-1].pid);
                psignal(WSTOPSIG(status), NULL);
            }
        }
        cjid = 0;
    }
}

