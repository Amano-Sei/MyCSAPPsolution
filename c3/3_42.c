/*************************************************************************
    > File Name: 3_42.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月06日 星期五 14时22分34秒
 ************************************************************************/

#include<stdio.h>

struct ELE{
    long v;
    struct ELE *p;
};

long fun(struct ELE *ptr){
    long result = 0;
    while(ptr != NULL){
        result += ptr->v;
        ptr = ptr->p;
    }
    return result;
}

