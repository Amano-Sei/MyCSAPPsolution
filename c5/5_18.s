	.file	"5_18.c"
	.text
	.globl	polyh
	.type	polyh, @function
polyh:
.LFB23:
	.cfi_startproc
	movapd	%xmm0, %xmm5
	mulsd	%xmm0, %xmm5
	movapd	%xmm0, %xmm4
	mulsd	%xmm5, %xmm4
	movapd	%xmm0, %xmm3
	mulsd	%xmm4, %xmm3
	movapd	%xmm0, %xmm1
	mulsd	%xmm3, %xmm1
	movapd	%xmm0, %xmm7
	pxor	%xmm8, %xmm8
	pxor	%xmm9, %xmm9
	pxor	%xmm10, %xmm10
	pxor	%xmm11, %xmm11
	pxor	%xmm2, %xmm2
	movsd	.LC1(%rip), %xmm6
	movl	$0, %eax
	jmp	.L2
.L3:
	movapd	%xmm6, %xmm12
	mulsd	(%rdi,%rax,8), %xmm12
	addsd	%xmm12, %xmm2
	movapd	%xmm7, %xmm12
	mulsd	8(%rdi,%rax,8), %xmm12
	addsd	%xmm12, %xmm11
	movapd	%xmm5, %xmm12
	mulsd	16(%rdi,%rax,8), %xmm12
	addsd	%xmm12, %xmm10
	movapd	%xmm4, %xmm12
	mulsd	24(%rdi,%rax,8), %xmm12
	addsd	%xmm12, %xmm9
	movapd	%xmm3, %xmm12
	mulsd	32(%rdi,%rax,8), %xmm12
	addsd	%xmm12, %xmm8
	mulsd	%xmm1, %xmm6
	mulsd	%xmm1, %xmm7
	mulsd	%xmm1, %xmm5
	mulsd	%xmm1, %xmm4
	mulsd	%xmm1, %xmm3
	addq	$5, %rax
.L2:
	leaq	-3(%rsi), %rdx
	cmpq	%rax, %rdx
	jg	.L3
	addsd	%xmm11, %xmm2
	addsd	%xmm10, %xmm2
	addsd	%xmm9, %xmm2
	addsd	%xmm8, %xmm2
	pxor	%xmm1, %xmm1
	jmp	.L4
.L5:
	mulsd	%xmm0, %xmm1
	addsd	(%rdi,%rax,8), %xmm1
	leaq	1(%rax), %rax
.L4:
	cmpq	%rsi, %rax
	jle	.L5
	movapd	%xmm1, %xmm0
	addsd	%xmm2, %xmm0
	ret
	.cfi_endproc
.LFE23:
	.size	polyh, .-polyh
	.globl	polyhwithhorner
	.type	polyhwithhorner, @function
polyhwithhorner:
.LFB24:
	.cfi_startproc
	movapd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	mulsd	%xmm0, %xmm1
	movapd	%xmm1, %xmm12
	pxor	%xmm1, %xmm1
	pxor	%xmm7, %xmm7
	pxor	%xmm14, %xmm14
	pxor	%xmm13, %xmm13
	pxor	%xmm11, %xmm11
	pxor	%xmm10, %xmm10
	pxor	%xmm9, %xmm9
	pxor	%xmm8, %xmm8
	pxor	%xmm6, %xmm6
	pxor	%xmm5, %xmm5
	jmp	.L7
.L8:
	leaq	0(,%rsi,8), %rax
	mulsd	%xmm12, %xmm5
	addsd	-72(%rdi,%rax), %xmm5
	mulsd	%xmm12, %xmm6
	addsd	-64(%rdi,%rax), %xmm6
	movapd	%xmm8, %xmm2
	mulsd	%xmm12, %xmm2
	addsd	-56(%rdi,%rax), %xmm2
	movapd	%xmm2, %xmm8
	movapd	%xmm9, %xmm2
	mulsd	%xmm12, %xmm2
	addsd	-48(%rdi,%rax), %xmm2
	movapd	%xmm2, %xmm9
	movapd	%xmm10, %xmm3
	mulsd	%xmm12, %xmm3
	addsd	-40(%rdi,%rax), %xmm3
	movapd	%xmm3, %xmm10
	movapd	%xmm11, %xmm3
	mulsd	%xmm12, %xmm3
	addsd	-32(%rdi,%rax), %xmm3
	movapd	%xmm3, %xmm11
	movapd	%xmm13, %xmm4
	mulsd	%xmm12, %xmm4
	addsd	-24(%rdi,%rax), %xmm4
	movapd	%xmm4, %xmm13
	movapd	%xmm14, %xmm4
	mulsd	%xmm12, %xmm4
	addsd	-16(%rdi,%rax), %xmm4
	movapd	%xmm4, %xmm14
	mulsd	%xmm12, %xmm7
	addsd	-8(%rdi,%rax), %xmm7
	mulsd	%xmm12, %xmm1
	addsd	(%rdi,%rsi,8), %xmm1
	subq	$10, %rsi
.L7:
	cmpq	$8, %rsi
	jg	.L8
	mulsd	%xmm0, %xmm1
	addsd	%xmm1, %xmm7
	mulsd	%xmm0, %xmm7
	addsd	%xmm14, %xmm7
	movapd	%xmm7, %xmm4
	mulsd	%xmm0, %xmm4
	addsd	%xmm13, %xmm4
	mulsd	%xmm0, %xmm4
	movapd	%xmm4, %xmm3
	addsd	%xmm11, %xmm3
	mulsd	%xmm0, %xmm3
	addsd	%xmm10, %xmm3
	mulsd	%xmm0, %xmm3
	movapd	%xmm3, %xmm2
	addsd	%xmm9, %xmm2
	mulsd	%xmm0, %xmm2
	addsd	%xmm8, %xmm2
	mulsd	%xmm0, %xmm2
	movapd	%xmm2, %xmm1
	addsd	%xmm6, %xmm1
	mulsd	%xmm0, %xmm1
	addsd	%xmm5, %xmm1
	jmp	.L9
.L10:
	mulsd	%xmm0, %xmm1
	addsd	(%rdi,%rsi,8), %xmm1
	leaq	-1(%rsi), %rsi
.L9:
	testq	%rsi, %rsi
	jns	.L10
	movapd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE24:
	.size	polyhwithhorner, .-polyhwithhorner
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC1:
	.long	0
	.long	1072693248
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
