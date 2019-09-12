/*************************************************************************
    > File Name: float_mov.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月09日 星期一 19时37分28秒
 ************************************************************************/

#include<stdio.h>

float float_mov(float v1, float *src, float *dst){
    float v2 = *src;
    *dst = v1;
    return v2;
}

