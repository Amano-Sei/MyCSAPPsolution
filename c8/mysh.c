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

extern char **environ;

struct Proc{
    char *volatile cmdline;
    volatile pid_t pid;
    volatile sig_atomic_t stat;
}proc[MAXARGS];
volatile sig_atomic_t tot = 0;
volatile sig_atomic_t cjid = 0;

void removejob(int jid);
int getargpid(char **argv);
int waitfg(int jid);

void eval(char *cmdline, sigset_t *prev);
int parseline(char *bur, char **argv);
int builtin_command(char **argv);

void sigchld_handler(int signum);
void kill_handler(int signum);

void builtin_jobs();
void builtin_bg(char **argv);
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
    cjid = 0;

    while(1){
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
        Sigprocmask(SIG_SETMASK, &prev, NULL);
        Sigprocmask(SIG_BLOCK, &mask, NULL);
        fflush(stdout);
    }
}

void removejob(int jid){
    if(jid <= 0)
        return;
    proc[jid-1].cmdline[0] = '\0';
    while(jid < tot){
        proc[jid-1].pid = proc[jid].pid;
        proc[jid-1].cmdline = proc[jid].cmdline;
        proc[jid-1].stat = proc[jid].stat;
        jid++;
    }
    if(jid == tot)
        tot--;
}

int waitfg(int jid){
    if(jid <= 0 || proc[jid-1].stat != 1)
        return -2;
    cjid = jid;
    int status;
    if(waitpid(proc[jid-1].pid, &status, WUNTRACED) < 0){
        perror("waitfg: waitpid error");
        exit(0);
    }

    if(WIFEXITED(status)){
        //printf("Job %d terminated normally with exit status=%d\n", proc[jid-1].pid, WEXITSTATUS(status));
        removejob(jid);
        cjid = 0;
        return 0;
    }else if(WIFSIGNALED(status)){
        fprintf(stderr, "Job %d terminated by signal: ", proc[jid-1].pid);
        psignal(WTERMSIG(status), NULL);
        removejob(jid);
        cjid = 0;
        return 0;
    }else if(WIFSTOPPED(status)){
        fprintf(stderr, "Job [%d] %d stopped by signal: ", jid, proc[jid-1].pid);
        psignal(WSTOPSIG(status), NULL);
        proc[jid-1].stat = 2;
        return -1;
    }else{
        fprintf(stderr, "waitfp: waitpid: unknowed return reason\n");
        exit(0);
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
                setpgid(0, 0);
                //因为shell会给当前进程组每个进程都发送SIGTSTP
                //所以要把他们分开
                if(execve(argv[0], argv, environ) < 0){
                    printf("%s: Command not found.\n", argv[0]);
                    exit(0);
                }
            }
            proc[tot].pid = pid;
            proc[tot].stat = ((bg<<1)+1);
            proc[tot++].cmdline = cmdline;
            if(!bg)
                waitfg(tot);
            else
                printf("[%d] %d %s", tot, pid, cmdline);
        }else{
            fprintf(stderr, "mysh: mysh can not have more than %d subprocesses.\n", MAXARGS);
        }
    }else
        cmdline[0] = '\0';
    return;
}

int builtin_command(char **argv){
    if(!strcmp(argv[0], "quit"))
        exit(0);
    if(!strcmp(argv[0], "&"))
        return 1;
    if(!strcmp(argv[0], "jobs")){
        builtin_jobs();
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
    while((pid=waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0){
        for(ci = 0; ci < tot && proc[ci].pid != pid; ci++);
        if(ci == tot){
            fprintf(stderr, "no such job %d, but received such pid\n", pid);
            exit(0);
        }

        if(WIFEXITED(status)){
            printf("Job %d terminated normally with exit status=%d\n", pid, WEXITSTATUS(status));
            removejob(ci+1);
        }else if(WIFSIGNALED(status)){
            fprintf(stderr, "Job %d terminated by signal: ", pid);
            psignal(WTERMSIG(status), NULL);
            removejob(ci+1);
        }else if(WIFSTOPPED(status)){
            fprintf(stderr, "Job [%d] %d stopped by signal: ", ci+1, pid);
            psignal(WSTOPSIG(status), NULL);
            proc[ci].stat = 2;
        }else if(WIFCONTINUED(status)){
            fprintf(stderr, "Job [%d] %d resumed by signal: SIGCONT\n", ci+1, pid);
            proc[ci].stat = 1;
        }else{
            fprintf(stderr, "pid %d returned for unknowed reason...\n", pid);
            exit(0);
        }
    }
}

void kill_handler(int signum){
    if(cjid > 0 && proc[cjid-1].stat == 1){
        //if(kill(proc[cjid-1].pid, signum) < 0){
        //从shell lab过来的，发觉应该是给那个job和他的所有子进程（
        //所以题目里才强调是前台进程组
        if(kill(-proc[cjid-1].pid, signum) < 0){
            perror("kill error");
            exit(0);
        }
    }
    putchar('\n');
}

void builtin_jobs(){
    for(int i = 0; i < tot; i++)
        if(proc[i].stat & 1)
            printf("[%d] %d Running    %s", i+1, proc[i].pid, proc[i].cmdline);
        else if(proc[i].stat == 2)
            printf("[%d] %d Stopped    %s", i+1, proc[i].pid, proc[i].cmdline);
        else{
            fprintf(stderr, "unkowned job: [%d] %d %d %s", i+1, proc[i].pid, proc[i].stat, proc[i].cmdline);
            exit(0);
        }
}

pid_t getargpid(char **argv){
    if(argv[1] == NULL){
        argv[1] = "current";
        if(cjid > 0)
            return proc[cjid-1].pid;
        return -1;
    }

    int tid;
    if(argv[1][0] == '%'){
        tid = atoi(&argv[1][1]);
        if(tid <= 0 || tid > tot)
            return -1;
        return proc[tid-1].pid;
    }else{
        tid = atoi(argv[1]);
        if(tid <= 0)
            return -1;
        return tid;
    }
}

void builtin_bg(char **argv){
    pid_t pid = getargpid(argv);
    if(pid < 0){
        printf("bg: %s: No such process\n", argv[1]);
        return;
    }
    int ret = kill(-pid, SIGCONT);
    if(ret < 0){
        if(errno == ESRCH){
            printf("bg: %s: No such process\n", argv[1]);
            return;
        }else if(errno == EPERM){
            printf("bg: %s: Permission denied\n", argv[1]);
            return;
        }
        perror("bg: kill");
        exit(0);
    }else{
        for(int i = 0; i < tot; i++)
            if(proc[i].pid == pid){
                proc[i].stat = 3;
                printf("[%d] %d %s", i+1, pid, proc[i].cmdline);
                return;
            }
        printf("bg: %s: No such process in job list, but it still continue\n", argv[1]);
    }
}

void builtin_fg(char **argv){
    pid_t pid = getargpid(argv);
    if(pid < 0){
        printf("fg: %s: No such process\n", argv[1]);
        return;
    }
    int ret = kill(-pid, SIGCONT);
    if(ret < 0){
        if(errno == ESRCH){
            printf("fg: %s: No such process\n", argv[1]);
            return;
        }else if(errno == EPERM){
            printf("fg: %s: Permission denied\n", argv[1]);
            return;
        }
        perror("fg: kill");
        exit(0);
    }else{
        for(int i = 0; i < tot; i++)
            if(proc[i].pid == pid){
                proc[i].stat = 1;
                waitfg(i+1);
                return;
            }
        printf("fg: %s: No such process in job list, but it still continue\n", argv[1]);
    }
}

