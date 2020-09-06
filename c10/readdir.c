/*************************************************************************
    > File Name: readdir.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月06日 星期日 09时29分04秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

void unix_error(char *from){
    fprintf(stderr, "%s error: %s\n", from, strerror(errno));
    exit(0);
}

int main(int argc, char **argv){
    DIR *dp;
    struct dirent *dep;
    if(argc != 2){
        printf("%s dirname\n", argv[0]);
        exit(0);
    }
    if((dp = opendir(argv[1])) == NULL)
        unix_error("opendir");
    errno = 0;
    while(dep = readdir(dp))
        printf("Found file: %s with %ld\n", dep->d_name, dep->d_ino);
    if(errno)
        unix_error("readdir");
    if(closedir(dp) < 0)
        unix_error("closedir");
    return 0;
}

