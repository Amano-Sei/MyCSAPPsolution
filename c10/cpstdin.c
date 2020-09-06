/*************************************************************************
    > File Name: cpstdin.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月01日 星期二 00时06分10秒
 ************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void unix_error(char *s){
    fprintf(stderr, "%s error: %s\n", s, strerror(errno));
    exit(0);
}

ssize_t Read(int fd, void *buf, size_t count){
    register ssize_t ret = read(fd, buf, count);
    if(ret < 0)
        unix_error("Read");
    return ret;
}

ssize_t Write(int fd, const void *buf, size_t count){
    register ssize_t ret = write(fd, buf, count);
    if(ret < 0)
        unix_error("Write");
    return ret;
}

int main(){
    char c;
    while(Read(STDIN_FILENO, &c, 1)){
        Write(STDOUT_FILENO, &c, 1);
        printf("==%x==", c);
        fflush(stdout);
    }
    exit(0);
}

