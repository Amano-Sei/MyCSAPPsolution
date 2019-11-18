/*************************************************************************
    > File Name: mysio.h
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月10日 星期日 20时28分14秒
 ************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

ssize_t my_sio_puts(char s[]);
void my_sio_error(char s[]);
ssize_t my_sio_putl(long v);

