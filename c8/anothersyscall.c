/*************************************************************************
    > File Name: anothersyscall.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年11月06日 星期三 16时05分08秒
 ************************************************************************/

int main(){
    syscall(1, 1, "ioridaisuki!\n", 13);
    syscall(60, 0);
    printf("done?\n");
}

