/*************************************************************************
    > File Name: 10_5.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月06日 星期日 11时18分50秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

//我们已经将fd1重定向到了fd2，所以从fd1读和继续读fd2是一样的

void unix_error(char *s){
    fprintf(stderr, "%s error: %s\n", s, strerror(errno));
    exit(0);
}

int main(){
    int fd1, fd2;
    char c;

    fd1 = open("foobar.txt", O_RDONLY, 0);
    if(fd1 < 0)
        unix_error("open");
    fd2 = open("foobar.txt", O_RDONLY, 0);
    if(fd2 < 0)
        unix_error("open");
    if(read(fd2, &c, 1) < 0)
        unix_error("read");
    if(dup2(fd2, fd1) < 0)
        unix_error("dup2");
    if(read(fd1, &c, 1) < 0)
        unix_error("read");
    printf("c = %c\n", c);
    exit(0);
}

