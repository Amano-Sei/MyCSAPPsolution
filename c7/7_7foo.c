/*************************************************************************
    > File Name: 7_7foo.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月04日 星期一 19时28分51秒
 ************************************************************************/

#include <stdio.h>

void f(void);

int y = 15212;
int x = 15213;

int main(){
    f();
    printf("x = 0x%x y = 0x%x \n", x, y);

    return 0;
}

