/*************************************************************************
    > File Name: foo5.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月31日 星期四 17时20分55秒
 ************************************************************************/

#include <stdio.h>

void f(void);

unsigned int y = 15212;
unsigned int x = 15213;

int main(){
    f();
    printf("x at %p, and x = %#x\ny at %p, and y = %#x\n", &x, x, &y, y);
    return 0;
}

