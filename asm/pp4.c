/*************************************************************************
    > File Name: pp4.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月12日 星期四 09时18分24秒
 ************************************************************************/

#include <stdio.h>

//int odd_parity(unsigned long x){
//    unsigned char *bx = (unsigned char *)&x;
//    unsigned char bresult = 0;
//    for(int i = 0; i < sizeof(unsigned long); i++)
//        asm("movb %[b], %%sil\n\t"
//            "testb %%sil, %%sil\n\t"
//            "setp %%bl\n\t"
//            "xorb %%bl, %[result]"
//            : [result] "=r" (bresult)
//            : [b] "m" (bx[i])
//            : "%bl", "%si"
//            );
//    return bresult;
//}
//上面的代码是错误的，不知道为什么编译器总是把bx当做指向8字节元素的指针
//另外setnp和setp在字节数是偶数时应该是等价的
//收回前言...等价的条件是完整地进行所有字节的testb
//但是答案的做法并不会完整地进行完

int odd_parity(unsigned long x){
    int result = 0;
    while(x){
        char bresult;
        asm("testq %[x], %[x]\n\t"
            "setnp %[v]"
            : [v] "=r" (bresult)
            : [x] "r" (x));
        x >>= 8;
        result ^= bresult;
    }
    return result;
}

int stans(unsigned long x){
    int result = 0;
    while(x != 0){
        char bresult;
        unsigned char bx = x & 0xff;
        asm("testb %[bx], %[bx]\n\t"
            "setnp %[v]"
            : [v] "=r" (bresult)
            : [bx] "r" (bx)
            );
        result ^= (int)bresult;
        x = x>>8;
    }
    return result;
}

int main(){
    unsigned long cur = 0;
    do{
        if(odd_parity(cur) != stans(cur)){
            printf("%llx\n", cur);
            printf("%d %d\n", odd_parity(cur), stans(cur));
            getchar();
        }
        if(cur % 0x10000000 == 0)
            printf("%d/... done...\n", cur/0x10000000);
        cur++;
    }while(cur);
    printf("跑完要到n年后了噗...\n");
}

