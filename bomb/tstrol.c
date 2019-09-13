/*************************************************************************
    > File Name: tstrol.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月13日 星期五 16时56分19秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

int main(){
    //说来惭愧，我没用过strol...
    char ts[11] = "  1010 123";
    char *pe;
    printf("%ld\n", strtol(ts, &pe, 11));
    printf("%d\n", pe-ts);
}

