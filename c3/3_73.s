	.file	"3_73.c"
	.text
	.globl	ori_find_range
	.type	ori_find_range, @function
ori_find_range:
.LFB23:
	.cfi_startproc
	pxor	%xmm1, %xmm1
	ucomiss	%xmm0, %xmm1
	ja	.L5
	ucomiss	%xmm1, %xmm0
	jp	.L8
	je	.L6
.L8:
	ucomiss	.LC0(%rip), %xmm0
	jbe	.L10
	movl	$2, %eax
	ret
.L5:
	movl	$0, %eax
	ret
.L6:
	movl	$1, %eax
	ret
.L10:
	movl	$3, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	ori_find_range, .-ori_find_range
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC1:
	.string	"%x %f\n"
.LC2:
	.string	"%d/16 done...\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movl	$0, %ebx
	jmp	.L14
.L12:
	addl	$1, %ebx
	testl	$268435455, %ebx
	je	.L16
.L13:
	testl	%ebx, %ebx
	je	.L17
.L14:
	movl	%ebx, uf(%rip)
	movl	%ebx, 12(%rsp)
	movss	12(%rsp), %xmm1
	movaps	%xmm1, %xmm0
	call	ori_find_range
	movl	%eax, %ebp
	pxor	%xmm0, %xmm0
	cvtss2sd	12(%rsp), %xmm0
	movl	$1, %eax
	call	find_range@PLT
	cmpl	%eax, %ebp
	je	.L12
	pxor	%xmm0, %xmm0
	cvtss2sd	uf(%rip), %xmm0
	movl	%ebx, %edx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$1, %eax
	call	__printf_chk@PLT
	jmp	.L12
.L16:
	movl	%ebx, %edx
	shrl	$28, %edx
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	jmp	.L13
.L17:
	movl	$0, %eax
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.comm	uf,4,4
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	0
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
