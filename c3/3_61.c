/*************************************************************************
    > File Name: 3_61.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 15时11分37秒
 ************************************************************************/

#include<stdio.h>

long cread(long *xp){
    return (xp ? *xp : 0);
}

long cread_alt(long *xp){
    long a = 0;
    return *(xp?xp:(&a));
    //这里自己在教室想了好久想到了，结果回来Og编译还是jmp傻眼
    //搜了别人答案发现和我是一样的
    //然后发现只有O1优化才是cmove
}

