/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "THE ALGORITHM@STER",
    /* First member's full name */
    "Amano Sei",
    /* First member's email address */
    "amano_sei@outlook.com",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)


#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define WSIZE 4
#define DSIZE 8
#define CHUNKSIZE (1<<12)
#define MSIZE 16

#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (unsigned int)(val))

//#define PACK(size, alloc) ((size) | (alloc))
#define PACK(size, alloc, prealloc) ((size) | (alloc) | (prealloc))

#define GET_SIZE(p) (GET(p) & ~0x7)
#define GET_ALLOC(p) (GET(p) & 0x1)
#define GET_PREV_ALLOC(p) (GET(p) & 0x2)

#define SET_PREV_ALLOC(p) PUT(p, (GET(p) | 0x2))

#define HDRP(bp) ((char *)(bp) - WSIZE)
#define NEXT_BLKP(bp) ((char *)(bp) + GET_SIZE(HDRP(bp)))

#define FTRP(bp) (NEXT_BLKP(bp) - DSIZE)
#define PREV_BLKP(bp) ((char *)(bp) - GET_SIZE((char *)(bp) - DSIZE))

#define SUCC(bp) (bp)
#define PRED(bp) ((char *)(bp)+WSIZE)
//出于一致性考虑，SUCC在低地址

#define MAX(a, b) ((a) > (b) ? (a) : (b))

static char *heap_listp;
static char *free_list;
//还没开始就遇到问题了，我意识到如果存void *的话，最小块大小会来到24B，还是存距离吧，这里的最大块大小也限制了距离不能超过size_t的范围

//然而蠢爆的我没有意识到size_t的范围是不同位数机器不同的。
//上面应该说是不超过unsigned int的范围。
//但是因为mdriver编译时有m32选项，所以干脆索性全32位好了
//用dis写实在是有点头晕，大不了回头再改回来。

//因为自己写的问题很多，而且因为realloc

static void *extend_heap(size_t size);
static void *ime_coalesce(void *bp);
static void def_coalesce();
static void *find_fit(size_t asize);
static void place(void *bp, size_t asize);
static size_t getsizeclass(size_t size);
static void delete_node(void *bp);
static void insert_node(void *bp, size_t sc);

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void){
    //mem_init();
    if((free_list = mem_sbrk(12 * WSIZE)) == (void *)-1)
        return -1;
    memset(free_list, 0, 11*WSIZE);
    PUT(free_list+11*WSIZE, PACK(0, 1, 2));
    if(extend_heap(CHUNKSIZE) == NULL)
        return -1;
    heap_listp = free_list+12*WSIZE;
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size){
    if(size == 0)
        return NULL;
    register size_t asize = MAX(MSIZE, ALIGN(size+WSIZE));
    register char *bp;
    if((bp = find_fit(asize)) == NULL){
        def_coalesce();
        if((bp = find_fit(asize)) == NULL)
            if((bp = extend_heap(asize)) == NULL)
                return NULL;
    }
    place(bp, asize);
    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *bp){
    register size_t cmsize = GET(HDRP(bp));
    register size_t csize = cmsize & ~0x7;
    register size_t cprea = cmsize & 0x2;
    PUT(HDRP(bp), PACK(csize, 0, cprea));
    PUT(FTRP(bp), PACK(csize, 0, 0));
    insert_node(bp, getsizeclass(csize));
    bp = HDRP(NEXT_BLKP(bp));
    PUT(bp, (GET(bp) & ~0x2));
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *bp, size_t size){
    register size_t csize = GET_SIZE(HDRP(bp));
    size = ALIGN(size+WSIZE);
    if(size < MSIZE)
        size = MSIZE;
    if(csize < size){
        register void *np = mm_malloc(size);
        if(np == NULL)
            return NULL;
        memcpy(np, bp, csize);
        mm_free(bp);
        bp = np;
    }else if(csize - size >= MSIZE){
        PUT(HDRP(bp), PACK(size, 1, GET_PREV_ALLOC(HDRP(bp))));
        register char *np = (char *)bp + size;
        csize -= size;
        PUT(HDRP(np), PACK(csize, 0, 0x2));
        PUT(FTRP(np), PACK(csize, 0, 0));
        insert_node(np, getsizeclass(csize));
        bp = HDRP(NEXT_BLKP(bp));
        PUT(bp, GET(bp) & (~0x2));
    }
    return bp;
}

/*
 * extend_heap - extend heap by size(bytes)
 *      when we call this function, we should make the number of consecutive not allocated blocks ahead the last block is one.
 *      It's mean that we should call coalesce or something others.
 */
static void *extend_heap(size_t size){
    size = MAX(size, CHUNKSIZE);
    void *p = mem_sbrk(size);
    if(p == (void *)-1)
        return NULL;
    if(GET_PREV_ALLOC(HDRP(p)) == 0){
        register size_t prevsize = GET_SIZE((char *)p - DSIZE);
        p = (char *)p - prevsize;
        delete_node(p);
        size += prevsize;
    }
    PUT(HDRP(p), PACK(size, 0, 0x2));
    PUT(FTRP(p), PACK(size, 0, 0));
    PUT(HDRP(NEXT_BLKP(p)), PACK(0, 1, 0));
    size_t csc = getsizeclass(size);
    insert_node(p, csc);
    return p;
}

/*
 * ime_coalesce - immediate coalescing, make use of HEAD, FOOT
 *      not for link list version
 */
static void *ime_coalesce(void *bp){
    size_t prev_alloc = GET_PREV_ALLOC(HDRP(bp));
    size_t next_alloc = GET_ALLOC(HDRP(NEXT_BLKP(bp)));
    size_t csize = GET_SIZE(HDRP(bp));
    if(!prev_alloc && !next_alloc){
        csize += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        bp = PREV_BLKP(bp);
        csize += GET_SIZE(HDRP(bp));
        PUT(HDRP(bp), PACK(csize, 0, GET_PREV_ALLOC(HDRP(bp))));
        PUT(FTRP(bp), PACK(csize, 0, 0));
    }else if(prev_alloc){
        csize += GET_SIZE(HDRP(NEXT_BLKP(bp)));
        PUT(HDRP(bp), PACK(csize, 0, prev_alloc));
        PUT(FTRP(bp), PACK(csize, 0, 0));
    }else if(next_alloc){
        bp = PREV_BLKP(bp);
        csize += GET_SIZE(HDRP(bp));
        PUT(HDRP(bp), PACK(csize, 0, GET_PREV_ALLOC(HDRP(bp))));
        PUT(FTRP(bp), PACK(csize, 0, 0));
    }
    return bp;
}

/*
 * def_coalesce - defered coalesce by scan free list
 *    also make use of HEAD, FOOT, PRED, SUCC
 */
static void def_coalesce(){
    //size_t maxsize = 0;
    for(int i = 1; i < 11; i++){
        register char *cp = (char *)GET(free_list+WSIZE*i);
        while(cp){
            register size_t csize = GET_SIZE(HDRP(cp));
            register size_t nsize = csize;
            register char *np = cp;
            while(GET_ALLOC(HDRP(np = NEXT_BLKP(np))) == 0){
                nsize += GET_SIZE(HDRP(np));
                delete_node(np);
            }
            np = cp;
            while(GET_PREV_ALLOC(HDRP(np)) == 0){
                np = PREV_BLKP(np);
                nsize += GET_SIZE(HDRP(np));
                delete_node(np);
            }
            register char *op = cp;
            cp = (char *)GET(SUCC(cp));
            //maxsize = MAX(maxsize, nsize);
            //本来是打算返回maxsize的，但是因为find_fit很快
            //所以这里频繁地求最大可能不合适
            if(nsize != csize){
                register size_t nsc = getsizeclass(nsize);
                PUT(HDRP(np), PACK(nsize, 0, 2));
                PUT(FTRP(np), PACK(nsize, 0, 0));
                delete_node(op);
                insert_node(np, nsc);
                //可以证明只要它吃了周围的块，就会成为更大的class
                //当然前提是同时只有def自己在管理这块内存。
            }
        }
    }
    //return maxsize;
}

/*
 * find_fit - find fit
 */
static void *find_fit(size_t asize){
    register size_t asc = getsizeclass(asize);
    for(char *hp = free_list+asc*WSIZE; asc < 11; hp += WSIZE, asc++){
        register char *cp = (char *)GET(SUCC(hp));
        while(cp){
            if(GET_SIZE(HDRP(cp)) >= asize)
                return cp;
            cp = (char *)GET(SUCC(cp));
        }
    }
    return NULL;
}

/*
 * place - place the block
 */
static void place(void *bp, size_t asize){
    delete_node(bp);
    register size_t csize = GET_SIZE(HDRP(bp));
    if(csize - asize < MSIZE){
        PUT(HDRP(bp), PACK(csize, 1, GET_PREV_ALLOC(HDRP(bp))));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), GET(HDRP(bp))|0x2);
    }else{
        PUT(HDRP(bp), PACK(asize, 1, GET_PREV_ALLOC(HDRP(bp))));
        bp = NEXT_BLKP(bp);
        PUT(HDRP(bp), PACK(csize-asize, 0, 0x2));
        PUT(FTRP(bp), PACK(csize-asize, 0, 0));
        insert_node(bp, getsizeclass(csize-asize));
    }
}

/*
 * getsizeclass - get size class
 */
static size_t getsizeclass(size_t size){
    if(size > 0x1000)
        return 0xa;
    register size_t ans = 1;
    register size_t csize = 0x10;
    while(size > csize){
        ans++;
        csize <<= 1;
    }
    return ans;
}

/*
 * delete_node - delete node, for link list
 */
static void delete_node(void *bp){
    register char *pre_node = (char *)GET(PRED(bp));
    register char *nxt_node = (char *)GET(SUCC(bp));
    PUT(SUCC(pre_node), nxt_node);
    if(nxt_node)
        PUT(PRED(nxt_node), pre_node);
}

/*
 * insert_node - insert node, for link list
 */
static void insert_node(void *bp, size_t sc){
    register char *list_header = free_list+sc*WSIZE;
    register char *nxt_node = (char *)GET(list_header);
    PUT(SUCC(bp), nxt_node);
    PUT(PRED(bp), list_header);
    PUT(list_header, bp);
    if(nxt_node)
        PUT(PRED(nxt_node), bp);
}









