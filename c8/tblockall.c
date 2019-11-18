/*************************************************************************
    > File Name: tblockall.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月11日 星期一 09时57分04秒
 ************************************************************************/

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(){
    sigset_t mask_all;
    sigfillset(&mask_all);
    sigprocmask(SIG_SETMASK, &mask_all, NULL);
    while(1){
        printf("blocker working...\n");
        sleep(1);
    }
}

