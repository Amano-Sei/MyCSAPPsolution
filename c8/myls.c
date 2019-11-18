/*************************************************************************
    > File Name: myls.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月12日 星期二 22时27分35秒
 ************************************************************************/

#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//我想我应该写的没有问题，但是设置COLUMNS环境变量并没有用
//可以看到即使设置了COLUMNS，在执行/bin/ls后会自动重新设置COLUMNS...

//作为代替，我们可以通过设置TZ环境变量借助./myls -l来判断是否接收到了正确的环境变量
//也可以选择直接在这里设置环境变量(不过如果前面设置了TZ应该会以第一次设置的TZ为准
//忘记说了，补一句，TZ的std offset是当前时间加上offset等于std，所以utc-8其实是东八区

//char desu[100] = "TZ=utc-8";

int main(int argc, char **argv){
    //int i = 0;
    //while(environ[i])
    //    i++;
    //environ[i] = desu;
    //environ[i+1] = NULL;
    if(execve("/bin/ls", argv, environ) < 0){
        fprintf(stderr, "execve error: %s\n", strerror(errno));
        exit(0);
    }
    return 0;
}

