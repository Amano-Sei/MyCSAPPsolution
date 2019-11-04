/*************************************************************************
    > File Name: 7_6.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月04日 星期一 19时01分55秒
 ************************************************************************/

extern int buf[];

int *bufp0 = &buf[0];
static int *bufp1;

static void incr(){
    static int count = 0;
    count++;
}

void swap(){
    int temp;

    incr();
    bufp1 = &buf[1];
    temp = *bufp0;
    *bufp0 = *bufp1;
    *bufp1 = temp;
}

