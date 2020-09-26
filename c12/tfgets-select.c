/*************************************************************************
    > File Name: tfgets-select.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月23日 星期三 11时14分00秒
 ************************************************************************/

#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream){
    int fd;
    int ret;
    struct timeval fivesec;
    fd_set readset;

    fd = fileno(stream);
    FD_ZERO(&readset);
    FD_SET(fd, &readset);
    fivesec.tv_sec = 5;
    fivesec.tv_usec = 0;

    ret = select(fd+1, &readset, NULL, NULL, &fivesec);
    if(ret < 0){
        fprintf(stderr, "select error: %s\n", strerror(errno));
        exit(0);
    }else if(ret == 0)
        return NULL;
    else
        return fgets(s, size, stream);
}

