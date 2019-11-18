/*************************************************************************
    > File Name: talarm.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月09日 星期六 18时54分45秒
 ************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int cnt;

void neverdesu(int signum){
    //cnt++;
    sigset_t mask, prev_mask;
    sigaddset(&mask, signum);
    sigprocmask(SIG_UNBLOCK, &mask, &prev_mask);
    if(cnt > 2){
        printf("\n\nwell...I will, but never forget me!!!\n");
        exit(0);
    }
    if(signum == SIGINT)
        printf("\n\nHA HA, you think you can stop with a CTRL+C?\nNEVER NEVER!!!\n\n");
    else if(signum == SIGTSTP)
        printf("\n\nHA HA, you think you can stop with a CTRL+Z?\nNEVER NEVER!!!\n\n");
    alarm(2);
    sleep(1);
}

int main(){
    //for(int i = 10; i > 0; i--){
    //    printf("%d\n", i);
    //    if(i == 1){
    //        alarm(1);
    //        printf("boom...\n");
    //    }
    //    sleep(1);
    //}
    if(signal(SIGKILL, SIG_IGN) == SIG_ERR)
        fprintf(stderr, "woo...I can't kill sigkill: %s\nBut I can BLOCK it HIA HIA HIA\n", strerror(errno));
    sigset_t mask, prev_mask;
    sigaddset(&mask, SIGKILL);
    if(sigprocmask(SIG_BLOCK, &mask, &prev_mask) < 0)
        fprintf(stderr, "no...I can't block sigkill(((: %s\n", strerror(errno));
    //printf("\n==%ld %ld===\n", (unsigned long)mask, (unsigned long)prev_mask);
    if(signal(SIGTSTP, neverdesu) == SIG_ERR)
        fprintf(stderr, "woo...I can't kill sigtstp: %s\n", strerror(errno));
    if(signal(SIGINT, neverdesu) == SIG_ERR)
        fprintf(stderr, "woo...I can't kill sigint: %s\n", strerror(errno));
    while(1){

        int t = alarm(2);
        if(t){
        printf("A bomb would burst in %d seconds, I disposaled it, ans set a new one in 2 seconds...\n", t);
        printf("and I'm at %d, YOU can NEVER catch me, hia hia hia...\n", getpid());
        }
        sleep(1);
        //pause();
    }
}

