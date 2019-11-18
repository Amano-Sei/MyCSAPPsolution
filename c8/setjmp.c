/*************************************************************************
    > File Name: setjmp.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月11日 星期一 20时25分27秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf buf;

int error1 = 0;
int error2 = 1;

void foo(void), bar(void);

int main(){
    switch(setjmp(buf)){
        case 0:
            foo();
            break;
        case 1:
            printf("Dectected an error1 condition in foo\n");
            break;
        case 2:
            printf("Dectected an error2 condition in bar\n");
            break;
        default:
            printf("Unknown error condition in ???\n");
    }
    exit(0);
}

void foo(void){
    if(error1)
        longjmp(buf, 1);
    bar();
}

void bar(void){
    if(error2)
        longjmp(buf, 2);
}

