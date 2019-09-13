/*************************************************************************
    > File Name: func4.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月12日 星期四 20时42分02秒
 ************************************************************************/

#include <stdio.h>

//x in %edi, y in %esi, z in %edx
int ori_func4(int x, int y, int z){
    int ans = z-y;
    int k = ((unsigned)ans >> 31);
    ans = k+ans;
    ans >>= 1;
    k = ans + y;
    if(k <= x){
        ans = 0;
        if(k >= x){
            return ans;
        }else{
            y = k+1;
            ans = ori_func4(x, y, z);
            return ans*2+1;
        }
    }else{
        z = k-1;
        ans = ori_func4(x, y, z);
        return ans*2;
    }
}
//以上是直译过来的代码，下面开始修改
int func4(int x, int y, int z){
    int k = z-y;
    k = ((int)(((unsigned)k>>31) + k) >> 1) + y;
    if(k < x)
        return 2*func4(x, k+1, z)+1;
    else if(k > x)
        return 2*func4(x, y, k-1);
    else
        return 0;
}

//显然第二个数是0，因为没有出现修改他的地方
//第一个数范围在[0x0,0xe]之间，不然就直接爆了
//起初忘掉了这个范围，推断负数应该死循环的但是直接爆了，还以为自己哪里搞错了（（（
//从反汇编代码中可以看出返回值需要是0，显然函数必须沿着k<=x返回
//虽然函数有一个递归，但是函数从来没有修改过x的值
//k是(z-y)在加上符号位除2，但是k是正数，并且y保持为0，所以加上符号位可以忽略掉
//再看退出条件是k==x，所以只要是k取过的值就都可以是正确答案，依次求得7,3,1,0
//再运行下面的main验证
//至此phase_4完毕

//其实一开始的时候我不知道单操作数的sar是算术右移一位，然后以为k恒为0...
//误打误撞地直接得出答案之一的0
//还长叹一口气，这什么数学问题，搞得这么复杂就这？？？
//↑无知的我真是对不起QAQ

int main(){
    for(int i = 0; i <= 0xe; i++)
        if(!func4(i, 0, 0xe))
            printf("%d\n", i);
}

