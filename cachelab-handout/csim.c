#include "cachelab.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

//Amano Sei
//amano_sei@outlook.com

//相较于题目额外实现了一下-v（其实也就多了三四行
//说实话我可以说是第一次好好用c写有命令行参数的程序
//有点意外没怎么debug...
//不过说实话感觉自己写的很烂（各种乱七八糟的变量用的稀烂，说是造*无误了（
//从行为上来说的并行因为不知道实际curE的大小所以也没有办法做到
//感觉为了可读性可以再写一个set结构体，然后给set上设一些参数在一些情况下提升速度
//但是实际上不管命不命中，都是要给所有有效block的cnt++的
//所以从这个软件层面来说避免不了扫一遍这件事
//（其实有个小小的例外，cold状态下可以不去扫，所以其实用个链表来实现比较好么（笑）
//但是毕竟是定长的而且E也不大，扫一遍也没有很大代价，所以定长数组还是最适合拿来缓存模拟的数据结构

//看了dalao的代码，自愧不如来重构了（顺便加上getopt
//结果只是拆了一半到run里面（真的写的是*QAQ

struct cblock{
    int isvalid;
    int cnt;
    unsigned long tag;
};

void printHelper(){
    printf("./csim: Missing required command line argument\n");
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\n");
    printf("Examples:\n");
    printf("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
    printf("  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

void run(int curs, int curE, int curb, char *filename, int verbose){
    int hits = 0, misses = 0, evictions = 0;
    char curin[100];
    unsigned long curaddr;
    struct cblock **caches = NULL;
    FILE *fp = NULL;
    if(curs <= 0 || curE <= 0 || curb <= 0 || !filename){
        printHelper();
        return;
    }
    fp = fopen(filename, "r");
    if(!fp){
        printHelper();
        return;
    }

    caches = (struct cblock **)malloc((1<<curs)*sizeof(struct cblock *));
    if(!caches)
        return;
    struct cblock *tcs = NULL;
    tcs = (struct cblock *)malloc((1<<curs)*curE*sizeof(struct cblock));
    if(!tcs)
        return;
    memset(tcs, 0, (1<<curs)*curE*sizeof(struct cblock));
    for(int i = 0; i < (1<<curs); i++){
        caches[i] = tcs;
        tcs += curE;
    }

    char tmps[100];
    int tnum;
    while(fgets(curin, 100, fp) != NULL){
        sscanf(curin,"%s%lx%s%d", tmps, &curaddr, tmps, &tnum);
        unsigned long curtag = curaddr >> (curs+curb);
        unsigned long curset = (curaddr >> curb) & ((1<<curs)-1);
        int toinserti = -1;
        int cmaxcnt = 0;
        int cmaxi = -1;
        switch(curin[1]){
            case 'M':
                hits++;
            case 'L':
            case 'S':
                if(verbose)
                    for(int i = 1; curin[i] && curin[i]!='\n'; i++)
                        putchar(curin[i]);
                for(int i = 0; i < curE; i++)
                    if(caches[curset][i].isvalid){
                        if(caches[curset][i].tag == curtag){
                            toinserti = -2;
                            caches[curset][i].cnt = 0;
                        }else{
                            caches[curset][i].cnt++;
                            if(caches[curset][i].cnt > cmaxcnt){
                                cmaxcnt = caches[curset][i].cnt;
                                cmaxi = i;
                            }
                        }
                    }else if(toinserti == -1)
                        toinserti = i;
                if(toinserti == -2){
                    hits++;
                    if(verbose)
                        printf(" hit");
                }else{
                    misses++;
                    if(verbose)
                        printf(" miss");
                    if(toinserti == -1){
                        evictions++;
                        toinserti = cmaxi;
                        if(verbose)
                            printf(" eviction");
                    }
                    caches[curset][toinserti].cnt = 0;
                    caches[curset][toinserti].isvalid = 1;
                    caches[curset][toinserti].tag = curtag;
                }
                if(curin[1] == 'M' && verbose)
                    printf(" hit");
                putchar('\n');
        }
    }
    free(caches[0]);
    free(caches);
    printSummary(hits, misses, evictions);
}

int main(int argc, char *argv[])
{
    int verbose = 0;
    int curs, curE, curb;
    char *filename = NULL;
    int opt;
    opterr = 0;
    while((opt = getopt(argc, argv, "b:s:t:E:v")) != -1){
        switch(opt){
            case 'b':
                curb = atoi(optarg);
                break;
            case 's':
                curs = atoi(optarg);
                break;
            case 't':
                filename = optarg;
                break;
            case 'v':
                verbose = 1;
                break;
            case 'E':
                curE = atoi(optarg);
                break;
            default:
                printHelper();
                return 0;
        }
    }
    run(curs, curE, curb, filename, verbose);

    return 0;
}
