/*************************************************************************
    > File Name: twrongsize.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月11日 星期三 16时16分26秒
 ************************************************************************/

#include <stdio.h>

int test(int a, int b, int *c){
    int result = 0x12345678;
    *c = a*b;
    asm("setae %[val] #看看注释还在么":[val] "=m" (result));
    //=r会报mismatch，=m虽然不会但是只更新了最低位字节
    //回头来看这里时，自己一开始忘记了这个文件的目的...还说上面是迷惑发言（
    //如果目标地址是一个内存的话，就不知道他本来是几个字节了
    return result;
}

int main(){
    int x = 0;
    printf("%x\n", test(2, 2, &x));
}

