/*************************************************************************
    > File Name: hex2dd.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月07日 星期一 08时34分40秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

int gethexbit(char c){
    if(c >= '0' && c <= '9')
        return c-'0';
    else if(c >= 'a' && c <= 'f')
        return c-'a'+10;
    else if(c >= 'A' && c <= 'F')
        return c-'A'+10;
    else
        return -1;
}

int gethex(char *s){
    if(!s[0] || !s[1])
        return -1;
    register int s1 = gethexbit(s[0]);
    if(s1 < 0)
        return -1;
    register int s2 = gethexbit(s[1]);
    if(s2 < 0)
        return -1;
    return s1*0x10+s2;
}

int main(int argc, char **argv){
    char buf[16];
    char cnum[8];
    memset(cnum, 0, sizeof(cnum));
    if(argc < 2){
        printf("%s hexaddress...\n", argv[0]);
        return 0;
    }
    for(int i = 1; i < argc; i++){
        register char *tp = argv[i];
        if(strncmp(tp, "0x", 2) == 0)
            tp += 2;
        register int fal = 0;
        for(int j = 0; j < 4; j++){
            register int thex =  gethex(tp+j*2);
            if(thex < 0)
                fal = 1;
            cnum[j] = thex;
        }
        if(fal){
            fprintf(stderr, "bad address: %s\n", argv[i]);
            continue;
        }
        if(inet_ntop(AF_INET, cnum, buf, 16) == NULL){
            fprintf(stderr, "inet_ntop error: %s\n", strerror(errno));
            continue;
        }
        printf("%s\n", buf);
    }
    return 0;
}

