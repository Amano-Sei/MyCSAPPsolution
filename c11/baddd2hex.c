/*************************************************************************
    > File Name: dd2hex.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月07日 星期一 09时26分03秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char **argv){
    unsigned char buf[4];
    if(argc < 2){
        fprintf(stderr, "%s ipaddress...\n", argv[0]);
        return 0;
    }

    for(int i = 1; i < argc; i++){
        register int ret = inet_pton(AF_INET, argv[i], buf);
        if(ret < 0)
            fprintf(stderr, "inet_pton error: %s\n", strerror(errno));
        else if(ret == 0)
            fprintf(stderr, "bad address: %s\n", argv[i]);
        else
            printf("0x%x%x%x%x\n", buf[0], buf[1], buf[2], buf[3]);
    }

    return 0;
}

