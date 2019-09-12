/*************************************************************************
    > File Name: tfget.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 23时21分45秒
 ************************************************************************/

#include <stdio.h>

int main(){
    char s[10];
    fgets(s, 5, stdin);
    printf("%s", s);
    fgets(s, 5, stdin);
    printf("%s", s);
}

