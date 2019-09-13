/*************************************************************************
    > File Name: phase_6.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月13日 星期五 09时54分06秒
 ************************************************************************/

#include <stdio.h>
//本来尝试锻炼自己的模拟汇编能力
//但是太他喵长了...而且那么多分支点，主要是跳转点实在是眼睛都要看花了
//还是先翻译成c再看吧...

int read_six_number(char *s, int *b);
void phase_6(char *s){
    int num[6];
    long *lnum[6];
    int *r13 = &num[0];
    read_six_number(s, num);
    int *r14 = &num[0];
    int r12 = 0;
L2:
    int *rbp = r13;
    int ans = r13[0];
    ans = ans-1;
    if((unsigned)ans > 5)
        explode_bomb();
    r12++;
    if(r12 == 6)
        goto L3;
    int ebx = r12;
L1:
    ans = num[ebx];
    if(ans == *rbp)
        explode_bomb();
    ebx++;
    if(ebx <= 5)
        goto L1;
    r13++;
    goto L2;
L3:
    //至此可以看出这是1~6的一个排列
    int *rsi = &num[6];
    int *rax = r14;
    int ecx = 7;

R1:
    int edx = ecx;
    edx = edx-*rax;
    *rax = edx;
    rax++;
    if(rsi != rax)
        goto R1;
    //上述代码把num[0~5]变为了自己和7的差
//因为推到最后和预想的差太多，从晕的这里开始重来

    int esi = 0;
    goto D4;
D1:
    rdx = rdx[1];//说真的有毒...这里...不过终于明白了...
    eax++;
    if(eax != ecx)
        goto D1;
    goto D3;
D2:
    long *rdx = 0x6032d0;
D3:
    //此时rdx为0x6032d0+0x10*(num[esi]-1)
    lnum[esi] = rdx;
    esi++;
    if(esi == 6)
        goto D5;
D4:
    int ecx = num[esi];
    if(ecx <= 1)
        goto D2;
    int eax = 1;
    long *rdx = 0x6032d0;
    goto D1;
D5:

    rbx = lnum[0];
    rax = &lnum[1];
    rsi = &lnum[6];
    rcx = rbx;

E1:
    rdx = *rax;
    rcx[1] = rdx;
    rax++;
    if(rax == rsi)
        goto E2;
    rcx = rdx;
E2:
    rdx[1] = 0;
//又晕了...不过好像明白...

    ebp = 5;
F1:
    rax = rbx[1];//大坑注意，这是一个双字
    if(rax[0]<rbx[0])
        explode_bomb();
    rbx = rbx[1];
    ebp--;
    if(ebp)
        goto F1;
    //由以上得知，我们需要排出一个使得0x6032d0开始的6个8字中每个8字第二个双字从大到小的序列
    //它是3 4 5 6 1 2
    //再和7取差，得到答案4 3 2 1 6 5
    //emmm终于干掉了...还有我从第一个关卡就看到却不知道怎么进的secret phase
    //上面的c代码存在各种重复定义和不规范使用，不想重翻译一遍了...搞了我快一天了QAQ
    //而且有的地方真的又是指针又是值...很蓝瘦...
    //↑其实从中午补了一觉之后才开始真的有大进展...

//    int esi = 0;
//    goto D4;
//D1://130
//    long *rdx = &edx[1];
//    eax++;
//    if(eax != ecx)
//        goto D1;
//    goto D3;
//D2://143
//    edx = 0x6032d0;
//D3://148
//    lnum[esi] = rdx;
//    esi++;
//    if(esi == 6)
//        goto D5;
//D4://163
//    int ecx = num[esi];
//    if(ecx <= 1)
//        goto D2;
//    int eax = 1;
//    long *edx = 0x6032d0;
//    goto D1;
//D5://183
////有点复杂，不知道怎么表达比较好，理解不够透彻，但是大概明白了
//    long *rbx = lnum[0];
//    long **rax = &lnum[1];
//    long **rsi = &lnum[6];
//    long *rcx = rbx;
//E1:
//    long *rdx = *rax;
//    rcx[1] = rdx;
//    rax++;
//    if(rsi == rax)
//        goto E2;
//    rcx = rdx;
//    goto E1;
//E2:
////晕了...
//    lnum[6] = 0;
//    ebp = 5;
//    eax = rbx[1][0];
//    if(rbx[0] >= eax)
//        boom();
//    rbx(lnum[i] => lnum[i+1]);
}

