	.file	"pp6.c"
	.text
	.globl	poly
	.type	poly, @function
poly:
.LFB23:
	.cfi_startproc
	leaq	8(%rsp), %r10
	.cfi_def_cfa 10, 0
	andq	$-32, %rsp
	pushq	-8(%r10)
	pushq	%rbp
	.cfi_escape 0x10,0x6,0x2,0x76,0
	movq	%rsp, %rbp
	pushq	%r10
	.cfi_escape 0xf,0x3,0x76,0x78,0x6
	subq	$72, %rsp
	movq	%fs:40, %rax
	movq	%rax, -24(%rbp)
	xorl	%eax, %eax
	addq	$1, %rsi
	vmovsd	.LC0(%rip), %xmm2
	vxorpd	%xmm3, %xmm3, %xmm3
	jmp	.L2
.L4:
	vmulsd	(%rdi), %xmm2, %xmm1
	vaddsd	%xmm1, %xmm3, %xmm3
	vmulsd	%xmm0, %xmm2, %xmm2
	subq	$1, %rsi
	leaq	8(%rdi), %rdi
.L2:
	testb	$31, %dil
	je	.L3
	testq	%rsi, %rsi
	jne	.L4
.L3:
	vxorpd	%xmm1, %xmm1, %xmm1
	vmovapd	%ymm1, -80(%rbp)
	vmulsd	%xmm0, %xmm0, %xmm1
	vmulsd	%xmm0, %xmm1, %xmm11
	vunpcklpd	%xmm11, %xmm1, %xmm1
	vmovsd	.LC0(%rip), %xmm6
	vunpcklpd	%xmm0, %xmm6, %xmm4
	vinsertf128	$0x1, %xmm1, %ymm4, %ymm4
	vmulsd	%xmm0, %xmm11, %xmm7
	vbroadcastsd	%xmm2, %ymm1
	vmulpd	%ymm4, %ymm1, %ymm1
	vbroadcastsd	%xmm7, %ymm10
	vmulpd	%ymm10, %ymm1, %ymm5
	vmulpd	%ymm5, %ymm10, %ymm4
	vmulpd	%ymm4, %ymm10, %ymm6
	vmulsd	%xmm7, %xmm7, %xmm11
	vmulsd	%xmm7, %xmm11, %xmm11
	vmulsd	%xmm7, %xmm11, %xmm11
	vxorpd	%xmm9, %xmm9, %xmm9
	vmovapd	%ymm9, %ymm8
	vmovapd	%ymm9, %ymm7
	jmp	.L5
.L6:
	vmulpd	(%rdi), %ymm1, %ymm2
	vaddpd	-80(%rbp), %ymm2, %ymm2
	vmovapd	%ymm2, -80(%rbp)
	vmulpd	32(%rdi), %ymm5, %ymm2
	vaddpd	%ymm2, %ymm7, %ymm7
	vmulpd	64(%rdi), %ymm4, %ymm2
	vaddpd	%ymm2, %ymm8, %ymm8
	vmulpd	96(%rdi), %ymm6, %ymm2
	vaddpd	%ymm2, %ymm9, %ymm9
	vbroadcastsd	%xmm11, %ymm2
	vmulpd	%ymm2, %ymm1, %ymm1
	vmulpd	%ymm2, %ymm5, %ymm5
	vmulpd	%ymm2, %ymm4, %ymm4
	vmulpd	%ymm2, %ymm6, %ymm6
	subq	$-128, %rdi
	subq	$16, %rsi
.L5:
	cmpq	$15, %rsi
	ja	.L6
	jmp	.L7
.L8:
	vmulpd	(%rdi), %ymm1, %ymm2
	vaddpd	-80(%rbp), %ymm2, %ymm2
	vmovapd	%ymm2, -80(%rbp)
	vmulpd	%ymm10, %ymm1, %ymm1
	addq	$32, %rdi
	subq	$4, %rsi
.L7:
	cmpq	$3, %rsi
	ja	.L8
	jmp	.L9
.L10:
	vmulsd	(%rdi), %xmm1, %xmm2
	vaddsd	%xmm2, %xmm3, %xmm3
	vmulsd	%xmm0, %xmm1, %xmm1
	subq	$1, %rsi
	leaq	8(%rdi), %rdi
.L9:
	testq	%rsi, %rsi
	jne	.L10
	vaddpd	-80(%rbp), %ymm7, %ymm7
	vaddpd	%ymm9, %ymm8, %ymm8
	vaddpd	%ymm8, %ymm7, %ymm7
	vmovapd	%ymm7, -80(%rbp)
	jmp	.L11
.L12:
	vaddsd	-80(%rbp,%rsi,8), %xmm3, %xmm3
	addq	$1, %rsi
.L11:
	cmpq	$3, %rsi
	jbe	.L12
	vmovapd	%xmm3, %xmm0
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L15
	addq	$72, %rsp
	popq	%r10
	.cfi_remember_state
	.cfi_def_cfa 10, 0
	popq	%rbp
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
.L15:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE23:
	.size	poly, .-poly
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
