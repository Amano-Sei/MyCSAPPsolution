/*************************************************************************
    > File Name: hostinfo.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月08日 星期二 18时49分01秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

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

int Getnameinfo(const struct sockaddr *sa, socklen_t salen,
        char *host, size_t hostlen,
        char *service, size_t servlen, int flags){
    int ret = getnameinfo(sa, salen, host, hostlen, service, servlen, flags);
    if(ret){
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(ret));
        exit(0);
    }
    return ret;
}

int main(int argc, char **argv){
    struct addrinfo *p, *listp, hints;
    char buf[8192];
    int flags;
    if(argc != 2){
        fprintf(stderr, "Usage: %s <domain name>\n", argv[0]);
        exit(0);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    Getaddrinfo(argv[1], NULL, &hints, &listp);
    flags = NI_NUMERICSERV;
    for(p = listp; p; p = p->ai_next){
        Getnameinfo(p->ai_addr, p->ai_addrlen, buf, 8192, NULL, 0, flags);
        printf("%s\n", buf);
    }
    freeaddrinfo(listp);
    return 0;
}

