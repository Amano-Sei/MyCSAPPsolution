	.file	"pp5.c"
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
	vmovsd	.LC0(%rip), %xmm3
	vxorpd	%xmm6, %xmm6, %xmm6
	jmp	.L2
.L4:
	vmulsd	(%rdi), %xmm3, %xmm1
	vaddsd	%xmm1, %xmm6, %xmm6
	vmulsd	%xmm0, %xmm3, %xmm3
	subq	$1, %rsi
.L2:
	testb	$31, %dil
	je	.L3
	testq	%rsi, %rsi
	jns	.L4
.L3:
	vxorpd	%xmm1, %xmm1, %xmm1
	vmovapd	%ymm1, -80(%rbp)
	vmulsd	%xmm0, %xmm0, %xmm1
	vmulsd	%xmm0, %xmm1, %xmm4
	vunpcklpd	%xmm4, %xmm1, %xmm2
	vmovsd	.LC0(%rip), %xmm7
	vunpcklpd	%xmm0, %xmm7, %xmm1
	vinsertf128	$0x1, %xmm2, %ymm1, %ymm1
	vmulsd	%xmm0, %xmm4, %xmm4
	jmp	.L5
.L6:
	vmulpd	(%rdi), %ymm1, %ymm2
	vaddpd	-80(%rbp), %ymm2, %ymm2
	vmovapd	%ymm2, -80(%rbp)
	vbroadcastsd	%xmm4, %ymm2
	vmulpd	%ymm2, %ymm1, %ymm1
	addq	$32, %rdi
	subq	$4, %rsi
.L5:
	cmpq	$2, %rsi
	ja	.L6
	jmp	.L7
.L8:
	vmulsd	(%rdi), %xmm1, %xmm5
	vaddsd	-80(%rbp), %xmm5, %xmm5
	vmovsd	%xmm5, -80(%rbp)
	vmulsd	%xmm0, %xmm1, %xmm2
	vmovsd	%xmm2, %xmm1, %xmm5
	vinsertf128	$0x0, %xmm5, %ymm1, %ymm1
	addq	$8, %rdi
	subq	$1, %rsi
.L7:
	testq	%rsi, %rsi
	jns	.L8
	vbroadcastsd	%xmm3, %ymm3
	vmulpd	-80(%rbp), %ymm3, %ymm3
	vmovapd	%ymm3, -80(%rbp)
	movl	$0, %eax
	jmp	.L9
.L10:
	vaddsd	-80(%rbp,%rax,8), %xmm6, %xmm6
	addq	$1, %rax
.L9:
	cmpq	$3, %rax
	jbe	.L10
	vmovapd	%xmm6, %xmm0
	movq	-24(%rbp), %rax
	xorq	%fs:40, %rax
	jne	.L13
	addq	$72, %rsp
	popq	%r10
	.cfi_remember_state
	.cfi_def_cfa 10, 0
	popq	%rbp
	leaq	-8(%r10), %rsp
	.cfi_def_cfa 7, 8
	ret
.L13:
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
