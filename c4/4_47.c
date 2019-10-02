/*************************************************************************
    > File Name: 4_47.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月02日 星期三 09时40分07秒
 ************************************************************************/

void bubble_a(long *data, long count){
    long last;
    long *pre, *cur, *end = data+count;
    for(last = count-1; last > 0; last--)
        for(pre = data, cur = data+1; cur != end; pre++, cur++)
            if(*pre > *cur){
                long t = *cur;
                *cur = *pre;
                *pre = t;
            }
}

