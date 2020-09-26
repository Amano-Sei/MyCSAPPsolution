/*************************************************************************
    > File Name: adder.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年09月11日 星期五 23时46分43秒
 ************************************************************************/

#include "csapp.h"

//我没找到不传name只传俩值的表格，看了别人的解法改了读入
//所以我也调整了下adder

int main(){
    int n1 = 0, n2 = 0;
    char *buf;
    char header[MAXLINE], content[MAXLINE];
    char *method = getenv("REQUEST_METHOD");
    if(method == NULL)
        method = "GET";
    if((buf = getenv("QUERY_STRING")) != NULL)
        sscanf(buf, "num1=%d&num2=%d", &n1, &n2);
    sprintf(content, "<h3>Welcome to add.com: "
                     "The Internet addition portal.</h3>\r\n"
                     "<p>The answer is: %d + %d = %ld</p>\r\n"
                     "<p>Thanks for visiting!</p>\r\n",
                     n1, n2, (long)n1+n2);
    printf("Connection: close\r\n"
           "Content-type: text/html;charset=UTF-8\r\n"
           "Content-length: %lu\r\n\r\n", strlen(content));
    if(strcasecmp(method, "HEAD"))
        printf("%s", content);
    fflush(stdout);
    exit(0);
}

