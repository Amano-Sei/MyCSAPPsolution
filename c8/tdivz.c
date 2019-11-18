/*************************************************************************
    > File Name: tdivz.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月06日 星期三 15时25分10秒
 ************************************************************************/

#include <stdio.h>

int main(){
    //int a = 1/0;
    double a = -1.0/0.0;
    float b = 0.0/0.0;
    printf("divide zero done...\n%lf %f\n", a, b);
    return 0;
}

