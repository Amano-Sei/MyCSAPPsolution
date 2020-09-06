/*************************************************************************
    > File Name: 10_2.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月06日 星期日 10时52分07秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

//根据书上的描述，两个文件描述符有各自的文件位置，所以两次结果都是'f'

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
    if(read(fd1, &c, 1) < 0)
        unix_error("read");
    if(read(fd2, &c, 1) < 0)
        unix_error("read");
    printf("c = %c\n", c);
    exit(0);
}

