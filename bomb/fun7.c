/*************************************************************************
    > File Name: fun7.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月13日 星期五 17时04分36秒
 ************************************************************************/

#include <stdio.h>

int ori_fun7(long *rdi, int esi){
    if(!rdi)
        goto L2;
    int edx = *(int *)rdi;
    if(edx <= esi)
        goto L1;
    rdi = rdi[1];//又是这个有毒式子...四字注意
    int eax = fun7(rdi, esi);
    eax = eax+eax;
    goto L3;
L1:
    eax = 0;
    if(esi == edx)
        goto L3;
    rdi = rdi[2];//8字
    eax = fun7(rdi, esi);
    eax = 2*eax+1;
    goto L3;
L2:
    eax = -1;
L3:
    return eax;
}

int fun7(long *px, int y){
    if(!px)
        return -1;
    int x = *px;
    if(x < y)
        return 2*fun7((long *)px[2], y);
    else if(x > y)
        return 2*fun7((long *)px[1], y)+1;
    else
        return 0;
}

