/*************************************************************************
    > File Name: nooutputnodie.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月18日 星期一 11时32分03秒
 ************************************************************************/

#include <unistd.h>

int main(){
    while(1)
        sleep(1);
    return 0;
}

