/*************************************************************************
    > File Name: 3_71.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 23时18分58秒
 ************************************************************************/

#include <stdio.h>
#define BUFSIZE 100

void good_echo(){
    char s[BUFSIZE];
    while(fgets(s, BUFSIZE, stdin))
        printf("%s", s);
        //for(int i = 0; s[i]; i++)
        //    putchar(s[i]);
}

int main(){
    good_echo();
}
