/*************************************************************************
    > File Name: gets.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月07日 星期六 18时15分09秒
 ************************************************************************/

#include<stdio.h>

char *gets(char *s){
    int c;
    char *dest = s;
    while((c = getchar()) != '\n' && c != EOF)
        *dest++ = c;
    if(c == EOF && dest == s)
        return NULL;
    *dest++ = '\0';
    return s;
}

void echo(){
    char buf[8];
    gets(buf);
    printf("%s\n", buf);
}

