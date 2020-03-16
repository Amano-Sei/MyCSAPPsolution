/*************************************************************************
    > File Name: outputnodie.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年03月17日 星期二 00时30分31秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>

int main(){
    while(1){
        printf("%d...\n", getpid());
        sleep(2);
    }
    return 0;
}

