/*************************************************************************
    > File Name: tgprof.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2019年10月18日 星期五 19时49分38秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define maxn 1000005

//丢人啊...快排怎么写都快忘干净了...

int nums[maxn];
int tosort[maxn];

void popsort(){
    //int flag;
    for(int i = 0; i < maxn-1; i++){
        //flag = 1;
        for(int j = 0; j < maxn-i-1; j++){
            int tbool = tosort[j]<tosort[j+1];
            int tmin = tbool?tosort[j]:tosort[j+1];
            int tmax = tbool?tosort[j+1]:tosort[j];
            tosort[j] = tmin;
            tosort[j+1] = tmax;
        }
            //if(tosort[j]>tosort[j+1]){
            //    int t = tosort[j];
            //    tosort[j] = tosort[j+1];
            //    tosort[j+1] = t;
            //    flag = 0;
            //}
            //学过第五章还写出上面的代码真是丢人啊...
            //不过这样就不能提前结束了（
        //if(flag)
        //    return;
    }
}

void quicksort(int L, int R){
    if(L >= R)
        return;
    int l = L;
    int r = R;
    while(l<r){
        while(l<r && tosort[r] >= tosort[L])
            r--;
        while(l<r && tosort[l] <= tosort[L])
            l++;
        int t = tosort[l];
        tosort[l] = tosort[r];
        tosort[r] = t;
    }
    int t = tosort[l];
    tosort[l] = tosort[L];
    tosort[L] = t;
    quicksort(L, l-1);
    quicksort(l+1, R);
}

int checkright(){
    for(int i = 0; i < maxn-1; i++)
        if(tosort[i] > tosort[i+1])
            return 0;
    return 1;
}
int main(){
    srand(time(NULL));
    for(int i = 0; i < maxn; i++)
        nums[i] = rand()%maxn;
    memcpy(tosort, nums, sizeof(nums));
    printf("%d\n", checkright());
    popsort();
    printf("%d\n", checkright());
    memcpy(tosort, nums, sizeof(nums));
    quicksort(0, maxn-1);
    printf("%d\n", checkright());
    return 0;
}

