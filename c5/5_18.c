/*************************************************************************
    > File Name: 5_18.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月20日 星期日 16时55分21秒
 ************************************************************************/

#include <stdio.h>

//起初以为只能用horner...导致了错误的方向（
double polyh(double a[], double x, long degree){
    long i;
    double x0 = 1;
    double x1 = x;
    double x2 = x*x;
    double x3 = x2*x;
    double x4 = x3*x;
    double x5 = x4*x;
    double result = 0;
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    for(i = 0; i < degree-3 ; i += 5){
        result = result + x0*a[i];
        result1 = result1 + x1*a[i+1];
        result2 = result2 + x2*a[i+2];
        result3 = result3 + x3*a[i+3];
        result4 = result4 + x4*a[i+4];
        x0 *= x5;
        x1 *= x5;
        x2 *= x5;
        x3 *= x5;
        x4 *= x5;
    }
    //私以为不应该是6*3a，而应该是5*5，而且刚好可以并行运算一个循环里所有的浮点乘(5+5个)
    //这样关键路径有两个5条上是一边是浮点乘一边是浮点加，由于并行运算的浮点乘最多10个，所以5个计算下一轮的x0~x4，5个计算要加的项
    //两边的延迟分别是1/5*5=1和浮点加吞吐量界限1
    //所以CPE上界为1
    result = result+result1+result2+result3+result4;
    result2 = 0;
    while(i <= degree)
        result2 = result2*x+a[i++];
    result = result+result2;
    return result;
}
double polyhwithhorner(double a[], double x, long degree){
    long i;
    double x10 = x*x*x*x*x*x*x*x*x*x;
    double result = 0;
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    double result5 = 0;
    double result6 = 0;
    double result7 = 0;
    double result8 = 0;
    double result9 = 0;
    for(i = degree; i > 8; i-=10){
        result = a[i-9]+x10*result;
        result1 = a[i-8]+x10*result1;
        result2 = a[i-7]+x10*result2;
        result3 = a[i-6]+x10*result3;
        result4 = a[i-5]+x10*result4;
        result5 = a[i-4]+x10*result5;
        result6 = a[i-3]+x10*result6;
        result7 = a[i-2]+x10*result7;
        result8 = a[i-1]+x10*result8;
        result9 = a[i]+x10*result9;
    }
    //emmm这么做是horner的改进，CPE上界显然是1.5
    //result = (result+result1*x)+(result2*x*x+result3*x*x*x)+(result4*x*x*x*x+result5*x*x*x*x*x)+(result6*x*x*x*x*x*x+result7*x*x*x*x*x*x*x)+(result8*x*x*x*x*x*x*x*x+result9*x*x*x*x*x*x*x*x*x);
    result = ((((((((result9*x+result8)*x+result7)*x+result6)*x+result5)*x+result4)*x+result3)*x+result2)*x+result1)*x+result;
    //因为是double所以展开了10路...
    while(i >= 0)
        result = result*x + a[i--];
    return result;
}

