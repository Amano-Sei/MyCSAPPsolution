/*************************************************************************
    > File Name: foro2ncopy.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月12日 星期六 09时58分53秒
 ************************************************************************/

#include <stdio.h>

long ncopy(long *src, long *dst, long len)
{
    long count = 0;
    long val;

    while (len > 0) {
	val = *src++;
	*dst++ = val;
	if (val > 0)
	    count++;
	len--;
    }
    return count;
}

