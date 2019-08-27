/*************************************************************************
    > File Name: 002.cpp
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年07月17日 星期三 18时35分53秒
 ************************************************************************/

#include <iostream>
#include <cstdio>

using namespace std;

typedef unsigned char *bytepointer;

void showbyte(bytepointer start, int len){
    for(int i = 0; i < len; i++)
        printf("%3.2x", start[i]);
    printf("\n");
}

int main(){
    printf("%x\n", 125);
    int a = 125;
    showbyte((bytepointer)&a, sizeof(int));
    double b = 125;
    showbyte((bytepointer)&b, sizeof(double));
    float c = 125;
    showbyte((bytepointer)&c, sizeof(c));

    short cx = -12345;
    unsigned cy = cx;
    showbyte((bytepointer)&cy, sizeof(unsigned));

    return 0;
}

