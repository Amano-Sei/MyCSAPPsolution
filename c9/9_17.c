/*************************************************************************
    > File Name: 9_17.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年07月29日 星期三 21时43分06秒
 ************************************************************************/

//我们需要一个用来保存上一次搜索地址的指针
//在mm_init中初始化它
//在find_fit中分成两端来循环
//在place中更新search_end
//即可达成目的

static char *search_end;

int mm_init(){
    //...
    //初始化heap_listp
    search_end = heap_listp;
    //...
    //...
}

static void *find_fit(size_t asize){
    register size_t csize;
    for(void *p = search_end; (csize=GET_SIZE(HDRP(p))) != 0; p = NEXT_BLKP(bp))
        if(csize >= asize && GET_ALLOC(HDRP(p)))
            return p;
    for(void *p = heap_listp; p != search_end; p = NEXT_BLKP(bp))
        if(csize >= asize && GET_ALLOC(HDRP(p)))
            return p;
    return NULL;
}

static void *place(void *bp, size_t asize){
    size_t csize = GET_SIZE(HDRP(bp));
    if(csize-asize >= 2*DSIZE){
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0));
        PUT(FTRP(bp), PACK(csize-asize, 0));
        search_end = bp;
    }else{
        PUT(HDRP(bp), PACK(csize, 1));
        PUT(FTRP(bp), PACK(csize, 1));
        search_end = NEXT_BLKP(bp);
    }
}

