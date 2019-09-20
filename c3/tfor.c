/*************************************************************************
    > File Name: tfor.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月18日 星期三 13时48分19秒
 ************************************************************************/

#include <stdio.h>
#define true 1

int tfor(){
    int i = 0;
    for(;; i++);
    return i;
}

int twhile(){
    int i = 0;
    while(true)
        i++;
    return i;
}

int tfortrue(){
    int i = 0;
    for(; true; i++);
    return i;
}

