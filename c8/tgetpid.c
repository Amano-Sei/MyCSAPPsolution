/*************************************************************************
    > File Name: tgetpid.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月07日 星期四 12时14分05秒
 ************************************************************************/

#include <sys/types.h>
#include <unistd.h>

int main(){
    printf("%d %d\n", getpid(), getppid());

    return 0;
}

