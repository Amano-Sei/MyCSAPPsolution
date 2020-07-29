/*************************************************************************
    > File Name: mmapcopy.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年04月08日 星期三 18时42分36秒
 ************************************************************************/

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int errno;

//说实话...这道题第一时间看到的时候毫无思路...
//看了答案才明白这么写，然后又是对着各种合计一千多行的文档看fa了dai半天...
//希望i/o那章会讲file descriptor什么的

int main(int argc, char **argv){
    struct stat fstu;

    if(argc != 2){
        printf("Usage: %s filename\n", argv[0]);
        exit(0);
    }

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1){
        printf("open error: %s\n", strerror(errno));
        exit(0);
    }

    if(fstat(fd, &fstu) == -1){
        printf("fstat error: %s\n", strerror(errno));
        exit(0);
    }
    int size = fstu.st_size;

    void *ptr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(ptr == ((void *) -1)){
        printf("mmap error: %s\n", strerror(errno));
        exit(0);
    }

    if(write(1, ptr, size) < 0){
        printf("write error: %s\n", strerror(errno));
        exit(0);
    }

    return 0;
}

