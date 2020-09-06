/*************************************************************************
    > File Name: 10_3.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月06日 星期日 10时55分07秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

//子进程继承了父进程的文件描述符，所以两个指向了相同的打开文件表项
//所以子进程对位置的修改反映到了父进程中

void unix_error(char *s){
    fprintf(stderr, "%s error: %s\n", s, strerror(errno));
    exit(0);
}

pid_t Fork(){
    register pid_t ret = fork();
    if(ret < 0)
        unix_error("fork");
    return ret;
}

int main(){
    int fd;
    char c;

    fd = open("foobar.txt", O_RDONLY, 0);
    if(fd < 0)
        unix_error("open");
    if(Fork() == 0){
        if(read(fd, &c, 1) < 0)
            unix_error("read");
        exit(0);
    }
    if(wait(NULL) < 0)
        unix_error("wait");
    if(read(fd, &c, 1) < 0)
        unix_error("read");
    printf("c = %c\n", c);
    exit(0);
}

