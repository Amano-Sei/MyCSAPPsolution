/*************************************************************************
    > File Name: tfgets-main.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月23日 星期三 10时34分23秒
 ************************************************************************/

#include "csapp.h"

char *tfgets(char *s, int size, FILE *stream);

int main(){
    char buf[MAXLINE];
    if(tfgets(buf, MAXLINE, stdin) == NULL)
        printf("BOOM\n");
    else
        printf("%s", buf);
    exit(0);
}

