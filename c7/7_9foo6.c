/*************************************************************************
    > File Name: 7_9foo6.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月04日 星期一 20时30分49秒
 ************************************************************************/

#include <stdio.h>

//必须要说一下，非常巧的是我的main的地址最高两位出现了很多次55...
//不过如果我想起用Og编译的话就不是55了(((
//而且题面也是说48（我真是蠢（（（
//我一度以为函数名是像一个指针一样的东西
//但是这个似乎从c语言的层面去理解搞不好可能产生偏差
//所以还是从机器层级来理解好了，main这个符号的内容保存在foo6的.text段，而bar6把这个符号保存的地址的内容取了一字节出来，所以就是main的第一个指令的二进制表示

void p2(void);

int main(){
    p2();
    printf("main at%p\n", main);
    return 0;
}

