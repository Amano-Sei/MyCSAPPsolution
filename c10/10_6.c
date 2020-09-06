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

//很显然，关了之后再打开，最小的是4

void unix_error(char *s){
    fprintf(stderr, "%s error: %s\n", s, strerror(errno));
    exit(0);
}

int main(){
    int fd1, fd2;
    if((fd1 = open("foo.txt", O_RDONLY, 0)) < 0)
        unix_error("open");
    if((fd2 = open("bar.txt", O_RDONLY, 0)) < 0)
        unix_error("open");
    if(close(fd2) < 0)
        unix_error("close");
    if((fd2 = open("baz.txt", O_RDONLY, 0)) < 0)
        unix_error("open");
    printf("fd2 = %d\n", fd2);
    exit(0);
}

