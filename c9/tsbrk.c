/*************************************************************************
    > File Name: tsbrk.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年07月12日 星期日 15时20分36秒
 ************************************************************************/

#include <unistd.h>
#include <stdio.h>
int main(){
    //可以看到如果不先printf的话，堆指针会在printf后发生变化
    //所以正如之前所了解的那样，printf会调用malloc然后修改堆指针。
    void *p = sbrk(0);
    printf("start:\n");
    printf("%p\n", p);
    p = sbrk(-1);
    printf("%p\n", p);
    printf("%p\n", sbrk(0));
    return 0;
}

