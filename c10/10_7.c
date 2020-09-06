/*************************************************************************
    > File Name: 10_7.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月06日 星期日 12时29分57秒
 ************************************************************************/

#include "csapp.h"

//只是简单地换成rio_readnb

int main(int argc, char **argv){
    int n;
    rio_t rio;
    char buf[MAXBUF];
    Rio_readinitb(&rio, STDIN_FILENO);
    while(n = Rio_readnb(&rio, buf, MAXBUF))
        Rio_writen(STDOUT_FILENO, buf, n);
    return 0;
}

