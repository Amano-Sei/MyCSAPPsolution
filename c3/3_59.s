	.file	"3_59.c"
	.text
	.globl	store_prod
	.type	store_prod, @function
store_prod:
.LFB12:
	.cfi_startproc
	movq	%rdx, %rcx      ;%rcx = yl
	sarq	$63, %rcx       ;%rcx = yh
	movq	%rsi, %r8       ;%r8 = xl
	sarq	$63, %r8        ;%r8 = xh
	imulq	%rdx, %r8       ;%r8 = xh*yl
	imulq	%rsi, %rcx      ;%rcx = yh*xl
	addq	%r8, %rcx       ;%rcx = xl*yh + xh*yl
	movq	%rsi, %rax      ;%rax = xl
	mulq	%rdx            ;%rax = (xl*yl)l %rdx = (xl*yl)h
	addq	%rcx, %rdx      ;%rdx = (xl*yl)h+xl*yh+xh*yl = ph
	movq	%rax, (%rdi)    ;*(long *)dest = pl
	movq	%rdx, 8(%rdi)   ;*((long *)dest) = ph
	ret
	.cfi_endproc
.LFE12:
	.size	store_prod, .-store_prod
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
