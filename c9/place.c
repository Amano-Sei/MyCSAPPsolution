/*************************************************************************
    > File Name: place.c
    > Author: Amano Sei
    > Mail: amano_sei@outlook.com 
    > Created Time: 2020年07月24日 星期五 22时40分03秒
 ************************************************************************/

//会发觉分配器部分的代码都写的很谨慎，括号一堆一堆的
//猜想是因为宏的原因

static void place(void *bp, size_t asize){
    register size_t size = GET_SIZE(HDRP(bp));
    if(size-asize >= DSIZE*2){
        PUT(HDRP(bp), PACK(asize, 1));
        PUT(FTRP(bp), PACK(asize, 1));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(size-asize, 0));
        PUT(FTRP(bp), PACK(size-asize, 0));
    }else{
        PUT(HDRP(bp), PACK(size, 1));
        PUT(FTRP(bp), PACK(size, 1));
    }
}

