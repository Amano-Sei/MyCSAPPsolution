/*************************************************************************
    > File Name: 4_7.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月24日 星期二 18时35分13秒
 ************************************************************************/

#include <stdio.h>

long pushtest();

int main(){
    for(int i = 0; i < 10000; i++)
        if(pushtest() != 0)
            printf("warning...\n");
        printf("done\n");
    return 0;
}

