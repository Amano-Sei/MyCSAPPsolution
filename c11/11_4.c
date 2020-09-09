/*************************************************************************
    > File Name: hostinfo.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月08日 星期二 19时27分01秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

//说实话，也算不上很麻烦，只是强转和一堆括号而已

int Getaddrinfo(const char *host, const char *service,
        const struct addrinfo *hints,
        struct addrinfo **result){
    int ret = getaddrinfo(host, service, hints, result);
    if(ret){
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(ret));
        exit(0);
    }
    return ret;
}

int main(int argc, char **argv){
    struct addrinfo *p, *listp, hints;
    char buf[8192];
    if(argc != 2){
        fprintf(stderr, "Usage: %s <domain name>\n", argv[0]);
        exit(0);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    //hints.ai_flags = AI_CANONNAME;
    Getaddrinfo(argv[1], NULL, &hints, &listp);
    for(p = listp; p; p = p->ai_next){
        inet_ntop(AF_INET, &(((struct sockaddr_in *)(p->ai_addr))->sin_addr), buf, 8192);
        printf("%s\n", buf);
        //printf("%p %s\n", p->ai_canonname, p->ai_canonname);
    }
    freeaddrinfo(listp);
    return 0;
}

