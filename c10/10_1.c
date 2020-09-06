/*************************************************************************
    > File Name: 10_1.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年08月22日 星期六 10时14分13秒
 ************************************************************************/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(){
    int fd1, fd2;
    if((fd1 = open("foo.txt", O_RDONLY, 0)) < 0){
        fprintf(stderr, "open error: %s\n", strerror(errno));
        exit(-1);
    }
    printf("fd1 = %d\n", fd1);
    if(close(fd1) < 0){
        fprintf(stderr, "close error: %s\n", strerror(errno));
        exit(-1);
    }
    //if(close(fd1) < 0){
    //    fprintf(stderr, "close 1 error: %s\n", strerror(errno));
    //    exit(-1);
    //}
    //可以看到，close一个无效的fd会设置errno，但不会终止进程
    if((fd2 = open("baz.txt", O_RDONLY, 0)) < 0){
        fprintf(stderr, "open 3 error: %s\n", strerror(errno));
        exit(-1);
    }
    printf("fd2 = %d\n", fd2);
    exit(0);
}

