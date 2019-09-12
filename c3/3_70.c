/*************************************************************************
    > File Name: 3_70.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 23时07分47秒
 ************************************************************************/

#include <stdio.h>

union ele{
    struct {
        long *p;
        long y;
    }e1;
    struct {
        long x;
        union ele *next;
    }e2;
};

void proc(union ele *up){
    up->e2.x = *(up->e2.next->e1.p) - up->e2.next->e1.y;
}

