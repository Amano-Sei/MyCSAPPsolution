/*************************************************************************
    > File Name: myt.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月31日 星期四 15时58分04秒
 ************************************************************************/

int tdesu[3] = { 1, 2, 3 };

int a;
int b = 0;
int c = 2;

int desu(int aa, int bb, int cc){
    static int a;
    static int b = 0;
    static int c = 2;
    a++;
    b++;
    c++;
    return a+b+c+aa+bb+cc;
}

