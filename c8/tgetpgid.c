/*************************************************************************
    > File Name: tgetpgid.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月09日 星期六 18时13分50秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
    while(1){
        printf("%d %d===%d %d\n", getpid(), getpgrp(), getppid(), getpgid(getppid()));
        setpgid(0,0);
        sleep(1);
    }
    return 0;
}

