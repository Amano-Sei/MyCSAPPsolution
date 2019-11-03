/*************************************************************************
    > File Name: foo6.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月31日 星期四 18时00分59秒
 ************************************************************************/

void f(void);

double x;

int main(){
    f();
    printf("x at %p and x = %lf\n", &x, x);
    return 0;
}

