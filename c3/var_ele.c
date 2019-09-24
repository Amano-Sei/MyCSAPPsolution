/*************************************************************************
    > File Name: var_ele.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年09月24日 星期二 14时07分48秒
 ************************************************************************/

int var_ele(long n, int A[n][n], long i, long j){
    return A[i][j];
}

int main(){
    int a[10][10] = {{1}};
    printf("%d\n", var_ele(1, a, 0, 0));
    return 0;
}

