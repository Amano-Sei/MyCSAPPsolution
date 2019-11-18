/*************************************************************************
    > File Name: restart.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月11日 星期一 20时51分54秒
 ************************************************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

#include "mysio.h"
#include "mysig.h"

sigjmp_buf buf;

void handler(int sig){
    siglongjmp(buf, 1);
}

int main(){
    if(!sigsetjmp(buf, 1)){
        Signal(SIGINT, handler);
        my_sio_puts("starting\n");
    }else
        my_sio_puts("restarting\n");

    while(1){
        if(sleep(1) < 0){
            my_sio_puts("sleep error...\n");
            //my_sio_puts(strerror(errno));
            //可以看到strerror也不在信号安全函数之列
            _exit(0);
        }
        my_sio_puts("processing...\n");
    }
    exit(0);
}

