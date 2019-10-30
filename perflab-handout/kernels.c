/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "THE ALOGORITHM@STER",              /* Team name */

    "Amano Sei",     /* First member full name */
    "Amano_Sei@outlook.com",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
    int blocksize = 16;
    for (int i = 0; i < dim; i+=blocksize)
        for (int j = 0; j < dim; j+=blocksize)
            for(int ii = i; ii < i+blocksize && ii < dim; ii++)
                for(int jj = j; jj < j+blocksize && jj < dim; jj++)
                    dst[RIDX(dim-1-jj, ii, dim)] = src[RIDX(ii, jj, dim)];
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

    initialize_pixel_sum(&sum);
    for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

void addpixel(pixel_sum *ans, pixel *src){
    ans->red += src->red;
    ans->green += src->green;
    ans->blue += src->blue;
}

void setpixel(pixel *dst, short red, short green, short blue){
    dst->red = red;
    dst->green = green;
    dst->blue = blue;
}

/*
 * smooth - Your current working version of smooth. 
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) 
{
    if(dim){
        int prered = 0;
        int pregreen = 0;
        int preblue = 0;
        int curred = (int)src[0].red+src[dim].red;
        int curgreen = (int)src[0].green+src[dim].green;
        int curblue = (int)src[0].blue+src[dim].blue;
        int nxtred = (int)src[1].red+src[dim+1].red;
        int nxtgreen = (int)src[1].green+src[dim+1].green;
        int nxtblue = (int)src[1].blue+src[dim+1].blue;
        setpixel(dst, (prered+curred+nxtred)/4, (pregreen+curgreen+nxtgreen)/4, (preblue+curblue+nxtblue)/4);
        for(int j = 1; j < dim; j++){
            prered = curred; pregreen = curgreen; preblue = curblue;
            curred = nxtred; curgreen = nxtgreen; curblue = nxtblue;
            if(j<dim-1){
                nxtred = (int)src[j+1].red+src[dim+j+1].red;
                nxtgreen = (int)src[j+1].green+src[dim+j+1].green;
                nxtblue = (int)src[j+1].blue+src[dim+j+1].blue;
                setpixel(&dst[j], (prered+curred+nxtred)/6, (pregreen+curgreen+nxtgreen)/6, (preblue+curblue+nxtblue)/6);
            }else{
                setpixel(&dst[j], (prered+curred)/4, (pregreen+curgreen)/4, (preblue+curblue)/4);
            }
        }
        
        for (int i = 1; i < dim; i++){
            if(i+1 < dim){
                prered = 0;
                pregreen = 0;
                preblue = 0;
                curred = (int)src[RIDX(i-1, 0, dim)].red+src[RIDX(i, 0, dim)].red+src[RIDX(i+1, 0, dim)].red;
                curgreen = (int)src[RIDX(i-1, 0, dim)].green+src[RIDX(i, 0, dim)].green+src[RIDX(i+1, 0, dim)].green;
                curblue = (int)src[RIDX(i-1, 0, dim)].blue+src[RIDX(i, 0, dim)].blue+src[RIDX(i+1, 0, dim)].blue;
                nxtred = (int)src[RIDX(i-1, 1, dim)].red+src[RIDX(i, 1, dim)].red+src[RIDX(i+1, 1, dim)].red;
                nxtgreen = (int)src[RIDX(i-1, 1, dim)].green+src[RIDX(i, 1, dim)].green+src[RIDX(i+1, 1, dim)].green;
                nxtblue = (int)src[RIDX(i-1, 1, dim)].blue+src[RIDX(i, 1, dim)].blue+src[RIDX(i+1, 1, dim)].blue;
                setpixel(&dst[RIDX(i, 0, dim)], (prered+curred+nxtred)/6, (pregreen+curgreen+nxtgreen)/6, (preblue+curblue+nxtblue)/6);
                for(int j = 1; j < dim; j++){
                    prered = curred; pregreen = curgreen; preblue = curblue;
                    curred = nxtred; curgreen = nxtgreen; curblue = nxtblue;
                    if(j+1<dim){
                        nxtred = (int)src[RIDX(i-1, j+1, dim)].red+src[RIDX(i, j+1, dim)].red+src[RIDX(i+1, j+1, dim)].red;
                        nxtgreen = (int)src[RIDX(i-1, j+1, dim)].green+src[RIDX(i, j+1, dim)].green+src[RIDX(i+1, j+1, dim)].green;
                        nxtblue = (int)src[RIDX(i-1, j+1, dim)].blue+src[RIDX(i, j+1, dim)].blue+src[RIDX(i+1, j+1, dim)].blue;
                        setpixel(&dst[RIDX(i, j, dim)], (prered+curred+nxtred)/9, (pregreen+curgreen+nxtgreen)/9, (preblue+curblue+nxtblue)/9);
                    }else{
                        setpixel(&dst[RIDX(i, j, dim)], (prered+curred)/6, (pregreen+curgreen)/6, (preblue+curblue)/6);
                    }
                }
            }else{
                prered = 0;
                pregreen = 0;
                preblue = 0;
                curred = (int)src[RIDX(i-1, 0, dim)].red+src[RIDX(i, 0, dim)].red;
                curgreen = (int)src[RIDX(i-1, 0, dim)].green+src[RIDX(i, 0, dim)].green;
                curblue = (int)src[RIDX(i-1, 0, dim)].blue+src[RIDX(i, 0, dim)].blue;
                nxtred = (int)src[RIDX(i-1, 1, dim)].red+src[RIDX(i, 1, dim)].red;
                nxtgreen = (int)src[RIDX(i-1, 1, dim)].green+src[RIDX(i, 1, dim)].green;
                nxtblue = (int)src[RIDX(i-1, 1, dim)].blue+src[RIDX(i, 1, dim)].blue;
                setpixel(&dst[RIDX(i, 0, dim)], (prered+curred+nxtred)/4, (pregreen+curgreen+nxtgreen)/4, (preblue+curblue+nxtblue)/4);
                for(int j = 1; j < dim; j++){
                    prered = curred; pregreen = curgreen; preblue = curblue;
                    curred = nxtred; curgreen = nxtgreen; curblue = nxtblue;
                    if(j<dim-1){
                        nxtred = (int)src[RIDX(i-1, j+1, dim)].red+src[RIDX(i, j+1, dim)].red;
                        nxtgreen = (int)src[RIDX(i-1, j+1, dim)].green+src[RIDX(i, j+1, dim)].green;
                        nxtblue = (int)src[RIDX(i-1, j+1, dim)].blue+src[RIDX(i, j+1, dim)].blue;
                        setpixel(&dst[RIDX(i, j, dim)], (prered+curred+nxtred)/6, (pregreen+curgreen+nxtgreen)/6, (preblue+curblue+nxtblue)/6);
                    }else{
                        setpixel(&dst[RIDX(i, j, dim)], (prered+curred)/4, (pregreen+curgreen)/4, (preblue+curblue)/4);
                    }
                }
            }
        }
    }
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

