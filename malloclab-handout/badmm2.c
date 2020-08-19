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

#define WSIZE 4
#define DSIZE 8
#define MSIZE 16
#define CHUNKSIZE (1<<12)

#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (unsigned int)(val));

#define SZOF(val) ((val)&~0x7)
#define ALOF(val) ((val)&0x1)
#define PAOF(val) ((val)&0x2)
#define BOOF(val) ((val)&0x4)

#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp)+SZOF(GET(HDRP(bp)))-DSIZE)
#define NEXT_BLKP(bp) ((char *)(bp)+SZOF(GET(HDRP(bp))))
#define PREV_BLKP(bp) ((char *)(bp)-SZOF(GET((char *)(bp)-DSIZE)))
#define SUCC(bp) (bp)
#define PRED(bp) ((char *)(bp)+WSIZE)
#define MAX(a, b) ({ typeof(a) _a=(a); typeof(b) _b=(b); _a>_b?_a:_b; })

static inline void insert_node(void *bp, void *header);
static inline void delete_node(void *bp);
static inline size_t getsc(size_t size);
static inline void *getfhd(size_t size);

static inline size_t place(void *bp, size_t hd, size_t asize);

static void print_list();
static void heap_checker();

static void *free_list;
static void *heap_listp;


/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void){
    if((free_list = mem_sbrk(12*WSIZE+CHUNKSIZE)) == (void *)-1)
        return -1;
    memset(free_list, 0, 11*WSIZE);
    PUT(free_list+11*WSIZE, CHUNKSIZE|0x2);
    PUT(free_list+10*WSIZE+CHUNKSIZE, CHUNKSIZE);
    PUT(free_list+11*WSIZE+CHUNKSIZE, 1);
    heap_listp = free_list+12*WSIZE;
    insert_node(heap_listp, getfhd(CHUNKSIZE));
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size){
    if(size == 0)
        return NULL;
    size = ALIGN(size+WSIZE);
    if(size < MSIZE)
        size = MSIZE;
    register void *bp = NULL;
    {
    register int i = getsc(size);
    register void *p = free_list+i*WSIZE;
    //for(int i = getsc(size), p = free_list+i*WSIZE;
    for(; i < 11; i++, p += WSIZE){
        bp = (void *)GET(p);
        while(bp != NULL){
            register size_t hd = GET(HDRP(bp));
            if(hd >= size){
                delete_node(bp);
                place(bp, hd, size);
                //heap_checker("malloc");
                return bp;
            }
            bp = (void *)GET(SUCC(bp));
        }
    }
    }
    register size_t psize = MAX(size, CHUNKSIZE);
    if((bp = mem_sbrk(psize)) == (void *)-1)
        return NULL;
    if(GET(HDRP(bp)) < 2){
        register size_t tsize = GET(bp-DSIZE);
        psize += tsize;
        bp -= tsize;
        delete_node(bp);
    }
    PUT(bp+psize-WSIZE, place(bp, psize|0x2, size));
    //heap_checker("malloc");
    return bp;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *bp){
    register size_t hd = GET(HDRP(bp))&~0x1;
    register void *nxtp = bp+SZOF(hd);
    register size_t nxt_hd = GET(HDRP(nxtp))&~0x2;
    if(!PAOF(hd)){
        bp = bp-GET(bp-DSIZE);
        register size_t pre_hd = GET(HDRP(bp));
        delete_node(bp);
        hd += pre_hd;
        if(!ALOF(nxt_hd)){
            delete_node(nxtp);
            hd += nxt_hd;
        }else
            PUT(HDRP(nxtp), nxt_hd);
    }else if(!ALOF(nxt_hd)){
        delete_node(nxtp);
        hd += nxt_hd;
    }else
        PUT(HDRP(nxtp), nxt_hd);

    PUT(HDRP(bp), hd);
    hd = hd&~0x2;
    PUT(bp+hd-DSIZE, hd);
    insert_node(bp, getfhd(hd));
    //heap_checker("free");
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *bp, size_t size){
    if(bp == NULL)
        return mm_malloc(size);
    if(size == 0){
        mm_free(bp);
        return NULL;
    }
    size = ALIGN(size+WSIZE);
    if(size < MSIZE)
        size = MSIZE;
    register size_t hd = GET(HDRP(bp));
    register size_t csize = SZOF(hd);
    if(csize<size){
        register void *nxtp = bp+csize;
        register size_t nxt_hd = GET(HDRP(nxtp));
        if(SZOF(nxt_hd) == 0){
            register size_t psize = MAX(size-csize, CHUNKSIZE);
            mem_sbrk(psize);
            PUT(nxtp+psize-WSIZE, place(bp, (psize+hd)&~0x1, size));
        }else if(ALOF(nxt_hd) == 0 && SZOF(nxt_hd)+csize >= size){
            delete_node(nxtp);
            register size_t nsize = SZOF(nxt_hd)+csize;
            if(nsize-size >= MSIZE){
                PUT(HDRP(bp), (hd&0x3)|size);
                PUT(HDRP(bp+size), (nsize-size)|0x2);
                PUT(bp+nsize-DSIZE, nsize-size);
                insert_node(bp+size, getfhd(nsize));
            }else{
                PUT(HDRP(bp), SZOF(nxt_hd)+hd);
                PUT(HDRP(bp+nsize), GET(HDRP(bp+nsize))|0x2);
            }
        }else if(ALOF(nxt_hd) == 0 && SZOF(GET(HDRP(nxtp+SZOF(nxt_hd)))) == 0){
            delete_node(nxtp);
            hd += SZOF(nxt_hd);
            csize = SZOF(hd);
            register size_t psize = MAX(size-csize, CHUNKSIZE);
            mem_sbrk(psize);
            PUT(bp+csize+psize-WSIZE, place(bp, (psize+hd)&~0x1, size));
        }else{
            register void *np = bp;
            register size_t nsize = csize;
            if(!ALOF(nxt_hd)){
                delete_node(nxtp);
                nsize += SZOF(nxt_hd);
            }
            if(!PAOF(hd)){
                register size_t psize = GET(np-DSIZE);
                np = np-psize;
                delete_node(np);
                nsize += psize;
            }
            if(nsize < size){
                register void *nnp = mm_malloc(size-WSIZE);
                memcpy(nnp, bp, csize-WSIZE);
                bp = nnp;

                PUT(HDRP(np), nsize|PAOF(GET(HDRP(np))));
                insert_node(np, getfhd(nsize));
                np = np+nsize-WSIZE;
                PUT(np-WSIZE, nsize);
                PUT(np, GET(np)&~0x2);
            }else if(nsize-size < MSIZE){
                PUT(HDRP(np), nsize|PAOF(GET(HDRP(np)))|1);
                memmove(np, bp, csize-WSIZE);
                bp = np;
                np = np+nsize-WSIZE;
                PUT(np, GET(np)|0x2);
            }else{
                PUT(HDRP(np), size|PAOF(GET(HDRP(np)))|1);
                memmove(np, bp, csize-WSIZE);
                bp = np;
                PUT(np+size-WSIZE, (nsize-size)|0x2);
                PUT(np+nsize-DSIZE, nsize-size);
                insert_node(np+size, getfhd(nsize-size));

                np = np+nsize-WSIZE;
                PUT(np, GET(np)&~0x2);
            }
        }
    }else if(csize-size >= MSIZE){
        register size_t nsize = csize-size;
        PUT(HDRP(bp), hd-nsize);

        register void *np = bp+size;
        register void *nnp = bp+csize;
        hd = GET(HDRP(nnp));

        if(ALOF(hd)){
            PUT(HDRP(nnp), hd&~0x2);
        }else{
            delete_node(nnp);
            nsize += SZOF(hd);
        }
        PUT(HDRP(np), nsize|0x2);
        PUT(np+nsize-DSIZE, nsize);
        insert_node(np, getfhd(nsize));
    }
    print_list();
    //heap_checker("realloc");
    return bp;
}

static inline void insert_node(void *bp, void *header){
    register void *predp = header;
    register void *succp = (void *)GET(header);
    while(succp && succp < bp){
        predp = succp;
        succp = (void *)GET(SUCC(succp));
    }
    PUT(SUCC(predp), bp);
    PUT(PRED(bp), predp);
    PUT(SUCC(bp), succp);
    if(succp)
        PUT(PRED(succp), bp);
}

static inline void delete_node(void *bp){
    register void *predp = (void *)GET(PRED(bp));
    register void *succp = (void *)GET(SUCC(bp));
    PUT(SUCC(predp), succp);
    if(succp)
        PUT(PRED(succp), predp);
}

static inline size_t getsc(size_t size){
    if(size > 0x1000)
        return 10;
    register size_t ans = 1;
    register size_t csize = 0x10;
    while(size > csize){
        ans++;
        csize <<= 1;
    }
    return ans;
}

static inline void *getfhd(size_t size){
    return free_list+getsc(size)*WSIZE;
}

//hd 空闲块本来的header
static inline size_t place(void *bp, size_t hd, size_t asize){
    register size_t csize = SZOF(hd);
    register size_t lsize = csize-asize;
    if(lsize <= MSIZE){
        PUT(HDRP(bp), hd|1);
        bp = bp+csize-WSIZE;
        PUT(bp, GET(bp)|0x2);
        return 0x3;
    }else{
        PUT(HDRP(bp), asize|0x1|PAOF(hd));
        bp = bp+asize;
        PUT(HDRP(bp), lsize|0x2);
        PUT(bp+lsize-DSIZE, lsize);
        insert_node(bp, getfhd(lsize));
        return 0x1;
    }
}

static void print_list(){
    static int ctimes = 0;
    printf("%dth list print start...\n", ++ctimes);
    register int cc = 0;
    void *p = heap_listp;
    register size_t hd = GET(HDRP(p));
    while(SZOF(hd) != 0){
        printf("block %d at %p:\n\tsize: %d %x\n\t", ++cc, p, SZOF(hd), SZOF(hd));
        if(ALOF(hd))
            puts("\talloced");
        else{
            puts("\tfree");
            printf("\tfooter: %p %u %x\n", FTRP(p), GET(FTRP(p)), GET(FTRP(p)));
        }
        if(PAOF(hd))
            puts("\tpre alloced");
        p = p+SZOF(hd);
        hd = GET(HDRP(p));
    }
    printf("%dth print end...with %x\n\n", ctimes, hd);
}

static void heap_checker(char *from){
    static size_t cc = 0;
    register size_t fbc = 0;
    register void *p = free_list+WSIZE;
    cc++;
    for(int i = 0; i < 10; i++, p += WSIZE){
        register void *bp = (void *)GET(p);
        while(bp){
            fbc++;
            PUT(HDRP(bp), GET(HDRP(bp))|0x4);
            bp = (void *)GET(SUCC(bp));
        }
    }
    p = heap_listp;
    register size_t prealloc = 2;
    register size_t hd;
    while((hd = GET(HDRP(p))) > 0xf){
        if(prealloc != PAOF(hd)){
            fprintf(stderr, "[line %d], pre alloc error after %s!\n", cc+5, from);
            exit(0);
        }
        prealloc = ALOF(hd)<<1;
        if(!prealloc){
            if(BOOF(hd)){
                PUT(HDRP(p), hd&~0x4);
                fbc--;
            }else{
                fprintf(stderr, "[line %d] a free block in heap, but not in free list after %s\n", cc+5, from);
                exit(0);
            }
            if(GET(FTRP(p)) != SZOF(hd)){
                fprintf(stderr, "[line %d] footer error: header = %x, foot = %x, after %s\n", cc+5, hd, GET(FTRP(p)), from);
                exit(0);
            }
        }
        p = NEXT_BLKP(p);
    }
    if(fbc != 0){
        fprintf(stderr, "[line %d] a block in free list, but not in heap after %s, fbc = %d\n", cc+5, from, fbc);
        exit(0);
    }
    //if(mem_heap_hi()+1 != p){
    //    fprintf(stderr, "[line %d] heap size wrong, top is %p, but end with %p, after %s\n", cc+5, mem_heap_hi(), p, from);
    //    exit(0);
    //}
}

