/*************************************************************************
    > File Name: testsm32s2c.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月15日 星期日 17时38分23秒
 ************************************************************************/

#include <stdio.h>

//如下，test_floatPower2的fpu指令版本翻译完毕
//但是入栈出栈什么的描述起来太麻烦了（其实也不麻烦...只是懒
//emmm参数好像是用栈传递了...
//返回值貌似还是用eax返回的的32位整型
//浮点数栈好像有清空掉自己操作的错觉
//看网上说返回浮点数是用st(0)
//算一个浮点乘，要从内存栈读出压入寄存器栈计算再出寄存器栈保存到内存上的栈上
//确实是好慢的指令集的感觉（（（

unsigned test_floatPower2(int x){
    union{
        unsigned u;
        float f;
    }result;
    result.u = 0;
    float sp;
    if((unsigned)x == 0x80000000)
        goto L29;
    float base = 2.0;
    if(x < 0)
        goto L40;
L31:
    if(x <= 0)
        goto L37;
    sp = 1.0;
    goto L34;
L40:
    x = -x;
    base = 0.5;
    goto L31;
L33:
    base = base * base;
    x >>= 1;
    if(x <= 0)
        goto L41;
L34:
    if(1&x == 0)
        goto L33;
    sp = sp*base;
    goto L33;
L37:
    sp = 1.0;
    goto L32;
L41:
    //st(0) = st(0) pop
L32:
    result.f = sp;
L29:
    return result.u;
}

