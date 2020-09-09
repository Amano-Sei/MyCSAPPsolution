/*************************************************************************
    > File Name: dd2hex.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月07日 星期一 09时51分09秒
 ************************************************************************/

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv){
    struct in_addr inaddr;
    int ret;
    if(argc != 2){
        fprintf(stderr, "Usage: %s <dotted-decimal>\n", argv[0]);
        exit(0);
    }
    ret = inet_pton(AF_INET, argv[1], &inaddr);
    if(ret < 0){
        fprintf(stderr, "inet_pton error: %s\n", strerror(errno));
        exit(0);
    }else if(ret == 0){
        fprintf(stderr, "inet_pton error: invalid dotted-dicimal address\n");
        exit(0);
    }
    printf("0x%x\n", ntohl(inaddr.s_addr));

    return 0;
}

