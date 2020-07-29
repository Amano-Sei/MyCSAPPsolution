/*************************************************************************
    > File Name: tsbrk2.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年07月12日 星期日 15时31分27秒
 ************************************************************************/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char nums[18]="0123456789012345\n";
void prnum(unsigned long long p){
    for(int i = 15; i >= 0; i--, p>>=4){
        register char cnum = p&0xf;
        if(cnum < 0xa)
            cnum += '0';
        else
            cnum += 0x57;
        nums[i] = cnum;
    }
    write(1, nums, 17);
}

int main(){
    void *p = sbrk(0);
    printf("start:\n");
    void *p2 = sbrk(0);
    printf("%p ~ %p\n", p, p2);
    p = sbrk(p-p2);
    p2 = sbrk(0);
    prnum(p);
    prnum(p2);
    //可以看到消除了printf的堆空间后，报错了
    //sbrk(p-p2);
    //free(p2);
    //类似的，free掉也会报错，虽然从现在的视点来看，原因不太一样。
    //当然，这是因为printf调用了malloc才行的原因
    //同时，会发现p2如果不在堆的范围内free它的话也会报错
    //类似的即使在范围内也报错了
    //看来sbrk应该还做类似free范围内所有分配的块的事情
    printf("%p ~ %p\n", p, p2);
    return 0;
}

