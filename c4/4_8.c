/*************************************************************************
    > File Name: 4_8.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月24日 星期二 18时40分26秒
 ************************************************************************/

#include <stdio.h>

unsigned long poptest();

int main(){
    for(int i = 0; i < 100000; i++)
        if(poptest() != 0xabcd)
            printf("warning...\n");
    printf("done...\n");
    return 0;
}

