/*************************************************************************
    > File Name: read_line.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月13日 星期五 17时52分34秒
 ************************************************************************/

#include <stdio.h>
//自己被自己不敢去看关于打印输入的机器代码的想法给蒙蔽了
//大概进入secret_phase的关键就在read_line了
//终于来到了最后了

int skip(char *rdi){
    //14个跳转点QAQ，啊啊啊哭了...
    //参数是谁啊啊啊
    int edx = rdi[0];
    if(edx == 0)
        goto L14;
    long rsi = rdi;
    int r10d = edx;
    int r9d = 0;
    goto L4;
L1:

L4:
    if(edx == 0x22)
        goto L8;
    r8 = rsi+1;
    if(1 != r9d)
        goto L1;
L14:
    r8 = rdi;
    rax = rdi;
    goto L7;
}

char *read_line(){
    //哇，上来调用了一个不知道什么鬼的skipQAQ
    int eax = skip();
}

//emmm...说是放弃不如说是这个方法应该不是学习的本意，折腾下去我相信自己能完全明白read_line和skip都是什么，但是代价太大了...
//所以在看了dalao的做法之后明白了要用gdb调试观察

