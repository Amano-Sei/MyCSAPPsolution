/*************************************************************************
    > File Name: 9_14.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年07月28日 星期二 23时43分52秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

void unix_error(char *s){
    fprintf(stderr, "%s error: %s\n", s, strerror(errno));
    exit(0);
}

int main(){
    int fd = open("hello.txt", O_RDWR);
    if(fd < 0)
        unix_error("open");

    struct stat fs;
    if(fstat(fd, &fs) < 0)
        unix_error("fstat");

    char *p = mmap(NULL, fs.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
    if(p == (void *)-1)
        unix_error("mmap");

    p[0] = 'J';

    if(close(fd) < 0)
        unix_error("close");

    return 0;
}

