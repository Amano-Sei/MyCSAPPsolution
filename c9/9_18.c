/*************************************************************************
    > File Name: 9_18.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年07月29日 星期三 22时09分57秒
 ************************************************************************/

//说实话一开始犹豫了，但是突然意识到，我们可以把最后首部尾部的最后三位利用起来
//后来发觉似乎只用两位就可以了，因为关键在于我们要知道前面那个块到底有没有被分配
//我自裁...书上已经说的非常清楚了...我给忘了...

//需要注意，最小块也变成了8字节。


#define GET_PREV_ALLOC(p) (GET(p) & 0x2)
#define SET_PREV_ALLOC(p) (PUT((p), GET(p) | 0x2))
#define CL_PREV_ALLOC(p) (PUT((p), GET(p) & ~0x2))
#define SET_ALLOC(p) (PUT((p), GET(p) | 0x1))
#define CL_ALLOC(p) (PUT((p), GET(p) & ~0x1))
#define SET_SIZE(p, size) (PUT((p), GET(p)&0x7|(size)))

void mm_init(){
    //...
    //...
    PUT(heap_listp+(3*WSIZE), 3);
    //...
}

void *mm_malloc(size_t size){
    size_t asize;
    size_t extendsize;
    char *bp;
    if(size == 0)
        return NULL;
    asize = (size+WSIZE+DSIZE-1)/DSIZE*DSIZE;
    if((bp = find_fit(asize)) != NULL){
        place(bp, asize);
        return bp;
    }
    extendsize = MAX(asize, CHUNKSIZE);
    if((bp = extend_heap(extendsize/WSIZE)) != NULL){
        place(bp, asize);
        return bp;
    }
    return NULL;
}

static void *extend_heap(size_t words){
    char *bp;
    size_t size;

    size = (word%2+word)*WSIZE;
    if((long)(bp = mem_sbrk(size)) == -1)
        return NULL;
    PUT(HDRP(bp), PACK(size, GET_PREV_ALLOC(HDRP(bp))));
    PUT(FTRP(bp), PACK(size, 0));
    PUT(HDRP(NEXT_BLKP(bp)), PACK(0, 1));
    return coalesce(bp);
}

void mm_free(void *bp){
    CL_ALLOC(HDRP(bp));
    CL_ALLOC(FTRP(bp));
    CL_PREV_ALLOC(HDRP(NEXT_BLKP(bp)));
    coalesce(bp);
}

static void *coalesce(void *bp){
    size_t prev_alloc = GET_PREV_ALLOC(HDRP(bp));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t size = GET_SIZE(HDRP(bp));
    if(prev_alloc && next_alloc)
        return bp;
    else if(prev_alloc){
        size += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        SET_SIZE(HDRP(bp), size);
        PUT(FTRP(bp), PACK(size, 0));
    }else if(next_alloc){
        size += GET_SIZE(HDRP(PREV_BLKP(bp)));
        bp = PREV_BLKP(bp);
        SET_SIZE(HDRP(bp), size);
        PUT(FTRP(bp), PACK(size, 0));
    }else{
        size += GET_SIZE(HDRP(PREV_BLKP(bp))) + GET_SIZE(FTRP(NEXT_BLKP(bp)));
        bp = PREV_BLKP(bp);
        SET_SIZE(HDRP(bp), size);
        PUT(FTRP(bp), PACK(size, 0));
    }
    return bp;
}

static void place(void *bp, size_t asize){
    size_t csize = GET_SIZE(HDRP(bp));
    if(csize-asize >= DSIZE){
        PUT(HDRP(bp), asize | GET_PREV_ALLOC(HDRP(bp)) | 1);
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 2));
        PUT(FTRP(bp), PACK(csize-asize, 0));
    }else{
        PUT(HDRP(bp), csize | GET_PREV_ALLOC(HDRP(bp)) | 1);
        PUT(FTRP(bp), PACK(csize, 1));
    }
}

