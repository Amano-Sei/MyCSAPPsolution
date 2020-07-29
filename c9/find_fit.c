/*************************************************************************
    > File Name: find_fit.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年07月24日 星期五 22时28分54秒
 ************************************************************************/

static char *heap_listp;

//还是for写的更好看一点...至于重复计算交给编译器去优化吧（

static void *find_fit(size_t asize){
    //char *bp = heap_listp;
    //size_t size;
    //while((size = GET_SIZE(HDRP(bp))) != 0){
    //    if(GET_ALLOC(HDRP(bp)) == 0 && size >= asize)
    //        return bp;
    //    bp = NEXT_BLKP(bp);
    //}
    for(void *bp = heap_listp; GET_SIZE(HDRP(bp)) > 0; bp = NEXT_BLKP(bp))
        if(GET_ALLOC(HDRP(bp)) == 0 && GET_SIZE(HDRP(bp)) >= asize)
            return bp;
    return NULL;
}

