/*************************************************************************
    > File Name: fstatcheck.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月06日 星期日 13时52分22秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>

//同上一题，很普通，只需要换成fstat函数即可...

void unix_error(char *s){
    fprintf(stderr, "%s error: %s\n", s, strerror(errno));
    exit(0);
}

int main(int argc, char **argv){
    struct stat stat;
    char *type, *readok;
    if(fstat(atoi(argv[1]), &stat) < 0)
        unix_error("fstat");

    if(S_ISREG(stat.st_mode))
        type = "regular";
    else if(S_ISDIR(stat.st_mode))
        type = "directory";
    else
        type = "other";

    if(stat.st_mode & S_IRUSR)
        readok = "ok";
    else
        readok = "no";

    printf("type: %s, read: %s\n", type, readok);
    return 0;
}

