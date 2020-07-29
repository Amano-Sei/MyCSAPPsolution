/*************************************************************************
    > File Name: mmapcopy_re.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年04月16日 星期四 19时14分19秒
 ************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>

//重写的目的是因为这道题一开始不会...
//然后其实现在还在懵逼...
//但是写的和之前的几乎一模一样，所以还是照着书上的搞个更好看的版本吧...

void unix_error(char *msg){
    fprintf(stderr, "%s error: %s\n", msg, strerror(errno));
    exit(0);
}

void mmapcopy(int fd, int size){
    void *ptr = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
    if(ptr == (void *)-1)
        unix_error("mmap");
    if(write(1, ptr, size) < 0)
        unix_error("write");
}

int main(int argc, char **argv){
    if(argc != 2){
        printf("Usage: %s <filename>\n", argv[0]);
        exit(0);
    }
    struct stat fs;
    int fd = open(argv[1], O_RDONLY);
    if(fd < 0)
        unix_error("open");
    if(fstat(fd, &fs) < 0)
        unix_error("fstat");
    mmapcopy(fd, fs.st_size);
    return 0;
}

