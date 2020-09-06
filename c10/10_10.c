/*************************************************************************
    > File Name: 10_10.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月06日 星期日 14时17分47秒
 ************************************************************************/

#include "csapp.h"

int main(int argc, char **argv){
    int n;
    rio_t rio;
    char buf[MAXLINE];
    if(argc == 2)
        Rio_readinitb(&rio, Open(argv[1], O_RDONLY, 0));
    else
        Rio_readinitb(&rio, STDIN_FILENO);
    while(n = Rio_readlineb(&rio, buf, MAXLINE))
        Rio_writen(STDOUT_FILENO, buf, n);
    return 0;
}

