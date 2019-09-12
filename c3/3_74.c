/*************************************************************************
    > File Name: 3_73.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月12日 星期四 11时49分57秒
 ************************************************************************/

#include <stdio.h>

typedef enum{NEG, ZERO, POS, OTHER} range_t;

range_t ori_find_range(float x){
    int result;
    if(x < 0)
        result = NEG;
    else if(x == 0)
        result = ZERO;
    else if(x > 0)
        result = POS;
    else
        result = OTHER;
    return result;
}

range_t find_range(float);

union{
    unsigned u;
    float f;
}uf;

int main(){
    unsigned cur = 0;
    do{
        uf.u = cur;
        if(ori_find_range(uf.f) != find_range(uf.f))
            printf("%x %f\n", cur, uf.f);
        if(cur % 0x10000000 == 0)
            printf("%d/16 done...\n", cur/0x10000000);
        cur++;
    }while(cur);
    printf("all done\n");
}

