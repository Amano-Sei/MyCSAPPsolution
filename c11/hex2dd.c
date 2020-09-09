/*************************************************************************
    > File Name: hex2dd.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月07日 星期一 09时42分19秒
 ************************************************************************/

#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

//自己蠢到现在写获取字符串里的数字还要用自己写的函数...
//明明可以用sscanf...
//虽然自己写的可能会快一点，但是代码效率和简洁度下降一大截。

//要点的话，就是要注意把主机顺序的地址转变为网络顺序。

int main(int argc, char **argv){
    struct in_addr inaddr;
    uint32_t tnum;
    char buf[16];
    if(argc != 2){
        printf("Usage: %s <hex number>\n", argv[0]);
        exit(0);
    }
    sscanf(argv[1], "%x", &tnum);
    inaddr.s_addr = htonl(tnum);
    if(inet_ntop(AF_INET, &inaddr, buf, 16) == NULL){
        fprintf(stderr, "inet_ntop error: %s\n", strerror(errno));
        exit(0);
    }
    printf("%s\n", buf);
    return 0;
}

