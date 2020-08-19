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
#define MSIZE 16

#define MAXSC 10
#define FHCOUNT ((MAXSC+3)&~0x1)

#define TRICKSIZE (2*128+2*8+2*16)
//#define CHUNKSIZE (1<<12)
#define CHUNKSIZE (1<<4)

#define GET(p) (*(unsigned int *)(p))
#define PUT(p, val) (*(unsigned int *)(p) = (unsigned int)(val))

#define SZOF(val) ((val) & ~0x7)
#define ALOF(val) ((val) & 0x1)
#define PAOF(val) ((val) & 0x2)
#define BOOF(val) ((val) & 0x4)

#define HDRP(bp) ((char *)(bp)-WSIZE)
#define FTRP(bp) ((char *)(bp)+SZOF(GET(HDRP(bp)))-DSIZE)

#define PREV_BLKP(bp) ((char *)(bp)-GET((char *)(bp)-DSIZE))
#define NEXT_BLKP(bp) ((char *)(bp)+SZOF(GET(HDRP(bp))))

#define SUCC(bp) (bp)
#define PRED(bp) ((char *)(bp)+WSIZE)

#define MAX(a, b) ({ typeof(a) _a = (a); typeof(b) _b = (b); _a > _b ? _a : _b; })

#define TRUE 1

static inline size_t place(void *bp, size_t hd, size_t asize);
static inline void *extend_heap(size_t psize);
static inline void *find_fit(size_t asize);
static inline size_t getsc(size_t csize);
static inline void insert_node(void *bp, size_t csize);
static inline void delete_node(void *bp);

static void heap_checker(char *fs);
static void print_list();

//(MAXSC+1) free headers, small(max 0x10 bytes) to big.
static void **free_header;
static void *heap_listp;

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void){
    //free_header = mem_sbrk(sizeof(void *)*FHCOUNT+TRICKSIZE+CHUNKSIZE);
    free_header = mem_sbrk(sizeof(void *)*FHCOUNT+CHUNKSIZE);
    if(free_header == (void *)-1)
        return -1;
    memset(free_header, 0, (FHCOUNT-1)*sizeof(void *));
    heap_listp = (void *)&free_header[FHCOUNT];

    PUT(HDRP(heap_listp), CHUNKSIZE|0x2);
    PUT(heap_listp+CHUNKSIZE-DSIZE, CHUNKSIZE);
    PUT(heap_listp+CHUNKSIZE-WSIZE, 0x1);
    insert_node(heap_listp, CHUNKSIZE);

    /*
    PUT(HDRP(heap_listp), (CHUNKSIZE+TRICKSIZE)|0x2);
    PUT(heap_listp+CHUNKSIZE+TRICKSIZE-DSIZE, CHUNKSIZE+TRICKSIZE);
    PUT(heap_listp+CHUNKSIZE+TRICKSIZE-WSIZE, 0x1);
    insert_node(heap_listp, CHUNKSIZE+TRICKSIZE);
    register void *cheater1 = mm_malloc(128);
    mm_malloc(8);
    register void *cheater2 = mm_malloc(128);
    mm_malloc(8);
    mm_free(cheater1);
    mm_free(cheater2);
    */

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
    register void *bp = find_fit(size);
    if(bp){
        delete_node(bp);
        register size_t hd = GET(HDRP(bp));
        register void *np = bp+SZOF(hd);
        if(place(bp, hd, size)){
            PUT(HDRP(np), GET(HDRP(np))|0x2);
        }
        return bp;
    }
    bp = extend_heap(size);
    if(bp){
        register size_t hd = GET(HDRP(bp));
        register void *np = bp+SZOF(hd);
        PUT(HDRP(np), place(bp, hd, size)|0x1);
        return bp;
    }
    return NULL;
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *bp){
    register size_t hd = GET(HDRP(bp))&~0x1;
    if(!ALOF(GET(HDRP(bp+SZOF(hd))))){
        delete_node(bp+SZOF(hd));
        hd += SZOF(GET(HDRP(bp+SZOF(hd))));
    }
    if(!PAOF(hd)){
        bp = bp-GET(bp-DSIZE);
        delete_node(bp);
        hd = SZOF(hd)+GET(HDRP(bp));
    }
    PUT(HDRP(bp), hd);
    PUT(bp+SZOF(hd)-DSIZE, SZOF(hd));
    insert_node(bp, SZOF(hd));
    bp = bp+SZOF(hd);
    PUT(HDRP(bp), GET(HDRP(bp))&~0x2);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *bp, size_t asize){
    //print_list();
    if(bp == NULL)
      return mm_malloc(asize);
    if(asize == 0){
        mm_free(bp);
        return NULL;
    }
    asize = ALIGN(asize+WSIZE);
    register size_t hd = GET(HDRP(bp));
    register size_t csize = SZOF(hd);
    if(csize >= asize){
        if(place(bp, hd, asize) == 0){
            PUT(HDRP(bp+csize), GET(HDRP(bp+csize))&~0x2);
        }
    }else{
        register void *nxtp = bp+csize;
        register size_t nxt_hd = GET(HDRP(nxtp));
        register size_t nxt_size = SZOF(nxt_hd);
        if(!ALOF(nxt_hd) && nxt_size+csize >= asize){
            delete_node(nxtp);
            if(place(bp, hd+nxt_size, asize) == 0x2){
                PUT(HDRP(nxtp+nxt_size), GET(HDRP(nxtp+nxt_size))|0x2);
            }
        }else if(!ALOF(nxt_hd) && SZOF(GET(HDRP(nxtp+nxt_size))) == 0){
            extend_heap(asize-nxt_size-csize);
            nxt_size = SZOF(GET(HDRP(nxtp)));
            PUT(HDRP(nxtp+nxt_size), place(bp, hd+nxt_size, asize)|0x1);
        }else if(SZOF(nxt_hd) == 0){
            extend_heap(asize-csize);
            nxt_size = MAX(asize-csize, CHUNKSIZE);
            PUT(HDRP(nxtp+nxt_size), place(bp, hd+nxt_size, asize)|0x1);
        }else{
            register void *np = bp;
            register size_t nsize = csize;
            if(!ALOF(nxt_hd)){
                delete_node(nxtp);
                nsize += nxt_size;
            }
            if(!PAOF(hd)){
                np = bp-GET(bp-DSIZE);
                nsize += GET(bp-DSIZE);
                delete_node(np);
            }
            if(nsize >= asize){
                if(np != bp){
                    memmove(np, bp, csize-WSIZE);
                    bp = np;
                }
                PUT(HDRP(np+nsize), place(np, nsize|0x2, asize)|(GET(HDRP(np+nsize))&~0x2));
            }else{
                register void *nnp = mm_malloc(asize-WSIZE);
                memcpy(nnp, bp, csize-WSIZE);
                PUT(HDRP(np), nsize|0x2);
                PUT(np+nsize-DSIZE, nsize);
                insert_node(np, nsize);
                PUT(HDRP(np+nsize), GET(HDRP(np+nsize))&~0x2);
                bp = nnp;
            }
        }
    }
    //print_list();
    //heap_checker("realloc");
    return bp;
}

/*
 * place - Place asize block into a free block with header hd,
 *         hd may not be in a free block really.
 *         PAY ATTENTION! it won't change anything not in the
 *         free block.
 *         Return the pre alloc mark for the next block.
 */
static inline size_t place(void *bp, size_t hd, size_t asize){
    register size_t csize = SZOF(hd);
    if(csize - asize < MSIZE){
        PUT(HDRP(bp), hd|1);
        return 0x2;
    }else{
        PUT(HDRP(bp), asize|(hd&0x2)|1);
        csize = csize-asize;
        PUT(HDRP(bp+asize), csize|0x2);
        PUT(bp+asize+csize-DSIZE, csize);
        insert_node(bp+asize, csize);
        return 0;
    }
}

/*
 * extend_heap - Extend heap with psize.
 *               PAY ATTENTION! It will delete the free block
 *               close to the front of the extend heap,
 *               it won't insert node or change the last alloced block 0/1.
 *               Tht ONLY three things it may do are call mem_sbrk, call
 *               delete node, PUT(HDRP(bp), hd).
 */
static inline void *extend_heap(size_t psize){
    psize = MAX(psize, CHUNKSIZE);
    void *bp = mem_sbrk(psize);
    if(bp == (void *)-1)
        return NULL;
    register size_t hd = GET(HDRP(bp));
    if(hd == 0x3){
        PUT(HDRP(bp), psize|0x2);
    }else{
        register size_t presize = GET(bp-DSIZE);
        bp -= presize;
        hd = GET(HDRP(bp))+psize;
        delete_node(bp);
        PUT(HDRP(bp), hd);
    }
    return bp;
}

/*
 * find_fit - Search free list for the minimum block bigger than asize.
 *            It will choose the early/lower address one when multiple
 *            one have the same propriate size, which one caused by
 *            the implementation of insert_node.
 *            Return NULL when there is no such one.
 */
static inline void *find_fit(size_t asize){
    for(int i = getsc(asize); i <= MAXSC; i++){
        register void *bp = free_header[i];
        while(bp){
            if(SZOF(GET(HDRP(bp))) >= asize)
                return bp;
            bp = (void *)GET(SUCC(bp));
        }
    }
    return NULL;
}

/*
 * getsc - Get size class of csize.
 */
static inline size_t getsc(size_t csize){
    //return 10;
    //if(csize > 0x2000)
    //    return 10;
    if(csize > (0x8<<MAXSC))
        return MAXSC;
    register size_t ans = 0, cc = 0x10;
    while(csize > cc){
        ans++;
        cc <<= 1;
    }
    return ans;
}

/*
 * insert_node - Insert free block node into appropriate free list,
 *               smaller block is alway before bigger one.
 */
static inline void insert_node(void *bp, size_t csize){
    register void *predp = (void *)&free_header[getsc(csize)];
    register void *succp = (void *)GET(predp);
    //while(succp && succp < bp){
    while(succp && (SZOF(GET(HDRP(succp))) < csize || (SZOF(GET(HDRP(succp)) ) == csize && succp < bp))){
    //while(succp && SZOF(GET(HDRP(succp))) <= csize){
        predp = succp;
        succp = (void *)GET(SUCC(succp));
    }
    PUT(SUCC(predp), bp);
    PUT(PRED(bp), predp);
    PUT(SUCC(bp), succp);
    if(succp)
        PUT(PRED(succp), bp);
}

/*
 * delete_node - Delete free block node from its free list.
 */
static inline void delete_node(void *bp){
    register void *predp = (void *)GET(PRED(bp));
    register void *succp = (void *)GET(SUCC(bp));
    PUT(SUCC(predp), succp);
    if(succp)
        PUT(PRED(succp), predp);
}

/*
 * heap_checker - Check the heap, such as whether block in 
 *                free list is in heap, whether pre alloc
 *                mark is right.
 */
static void heap_checker(char *fs){
    register int fbn = 0;
    for(int i = 0; i <= MAXSC; i++){
        register void *p = free_header[i];
        while(p){
            fbn++;
            PUT(HDRP(p), GET(HDRP(p))|0x4);
            p = (void *)GET(SUCC(p));
        }
    }
    register void *p = heap_listp;
    register size_t hd = GET(HDRP(p));
    register size_t prealloc = 0x2;
    while(TRUE){
        if(PAOF(hd) != prealloc){
            fprintf(stderr, "error after %s: pre alloc mark error\n", fs);
            exit(0);
        }
        if(!ALOF(hd)){
            if(BOOF(hd)){
                fbn--;
                PUT(HDRP(p), hd&~0x4);
            }else{
                fprintf(stderr, "error after %s: free block not in free list\n", fs);
                exit(0);
            }
            prealloc = 0;
        }else
            prealloc = 0x2;
        if(hd < MSIZE)
            break;
        p += SZOF(hd);
        hd = GET(HDRP(p));
    }
    if(fbn != 0){
        fprintf(stderr, "error after %s: the number of free blocks in free list is not the same as the one of free blocks in heap, fbn = %u\n", fs, fbn);
        exit(0);
    }
}

/*
 * print_list - Print all block in heap from low address to high.
 */
static void print_list(){
    register void *p = heap_listp;
    register size_t hd = GET(HDRP(p));
    register size_t cc = 0;
    while(TRUE){
        printf("block %d: at %p\n", cc++, p);
        printf("\theader: %u %x\n", hd, hd);
        printf("\tsize: %u %x\n", SZOF(hd), SZOF(hd));
        if(PAOF(hd))
            printf("\tpre alloced\n");
        if(ALOF(hd)){
            printf("\talloced\n");
        }else{
            printf("\tfree\n");
            printf("\tfooter: %u %x\n", GET(p+SZOF(hd)-DSIZE), GET(p+SZOF(hd)-DSIZE));
        }
        if(hd < MSIZE)
            return;
        p += SZOF(hd);
        hd = GET(HDRP(p));
    }
}

