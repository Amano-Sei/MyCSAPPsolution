/*************************************************************************
    > File Name: mysio.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月10日 星期日 20时31分19秒
 ************************************************************************/

#include "mysio.h"

static size_t my_sio_strlen(char s[]){
    int i = 0;
    while(s[i] != '\0')
        i++;
    return i;
}

static void my_sio_reverse(char s[]){
    int c, i, j;
    for(i = 0, j = my_sio_strlen(s)-1; i < j; i++, j--){
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

static long my_sio_ltoa(long v, char s[], int b){
    int c, i = 0;
    do{
        s[i++] = ((c = (v % b)) < 10) ? c+'0' : c+'a';
    }while((v/=b) > 0);
    s[i] = '\0';
    my_sio_reverse(s);
}

ssize_t my_sio_puts(char s[]){
    return write(STDOUT_FILENO, s, my_sio_strlen(s));
}

void my_sio_error(char s[]){
    my_sio_puts(s);
    _exit(1);
}

ssize_t my_sio_putl(long v){
    char s[128];
    my_sio_ltoa(v, s, 10);
    return my_sio_puts(s);
}

