/*************************************************************************
    > File Name: myecho.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月07日 星期四 21时48分32秒
 ************************************************************************/

#include <stdio.h>

int main(int argc, char *argv[], char *envp[]){
    int i;
    printf("Command-line arguments:\n");
    for(i = 0; argv[i] != NULL; i++)
        printf("\targv[%2d]: %s\n", i, argv[i]);
    printf("Environment variables:\n");
    for(i = 0; envp[i] != NULL; i++)
        printf("\tenvp[%2d]: %s\n", i, envp[i]);
    return 0;
}

