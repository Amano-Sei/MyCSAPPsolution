/*************************************************************************
    > File Name: tgetenv.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月07日 星期四 21时42分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("%s\n", getenv("PATH"));

    return 0;
}

