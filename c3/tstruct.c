/*************************************************************************
    > File Name: tstruct.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月10日 星期二 21时56分43秒
 ************************************************************************/

#include<stdio.h>

typedef struct{
    long i, j;
    long *k;
} desu;

desu t1(){
    desu ans;
    return ans;
}

desu t2(int a){
    desu ans;
    return ans;
}

desu t3(int a, int b){
    desu ans;
    ans.i = a;
    ans.j = b;
    return ans;
}

desu t4(int a, int b, int c, int d, int e, int f, int g, desu h){
    desu ans;
    ans.i = a+b+c+d+e+f+g+h.i;
    return ans;
}

desu t5(desu h, int a, int b, int c, int d, int e, int f, int g){
    desu ans;
    ans.i = a+b+c+d+e+f+g+h.i;
    return ans;
}

