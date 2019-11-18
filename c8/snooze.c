/*************************************************************************
    > File Name: snooze.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月07日 星期四 15时19分10秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

//这里是8.7和8.5

void justchangeline(int signum){
    putchar('\n');
}

unsigned int snooze(unsigned int secs){
    int ans = sleep(secs);
    if(ans < 0){
        fprintf(stderr, "sleep error: %s\n", strerror(errno));
        exit(0);
    }
    printf("Slept for %d of %d secs.\n", secs-ans, secs);
    return ans;
}

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "usage: %s <secs>\n", argv[0]);
        exit(0);
    }
    if(signal(SIGINT, justchangeline) == SIG_ERR){
        fprintf(stderr, "signal error: %s\n", strerror(errno));
        exit(0);
    }
    snooze(atoi(argv[1]));
    return 0;
}

