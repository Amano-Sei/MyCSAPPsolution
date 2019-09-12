	.file	"tfcmp.c"
	.text
	.globl	tfcmp1
	.type	tfcmp1, @function
tfcmp1:
.LFB23:
	.cfi_startproc
	jmp	.L2
.L3:
	vaddsd	.LC0(%rip), %xmm0, %xmm0
	movl	(%rdi), %eax
	addl	$1, %eax
	movl	%eax, (%rdi)
.L2:
	vsubsd	%xmm1, %xmm0, %xmm2
	vxorpd	%xmm3, %xmm3, %xmm3
	vucomisd	%xmm2, %xmm3
	ja	.L3
	rep ret
	.cfi_endproc
.LFE23:
	.size	tfcmp1, .-tfcmp1
	.globl	tfcmp2
	.type	tfcmp2, @function
tfcmp2:
.LFB24:
	.cfi_startproc
	jmp	.L5
.L6:
	vaddsd	.LC0(%rip), %xmm0, %xmm0
	movl	(%rdi), %eax
	addl	$1, %eax
	movl	%eax, (%rdi)
.L5:
	vucomisd	%xmm0, %xmm1
	jnb	.L6
	rep ret
	.cfi_endproc
.LFE24:
	.size	tfcmp2, .-tfcmp2
	.globl	tfcmp3
	.type	tfcmp3, @function
tfcmp3:
.LFB25:
	.cfi_startproc
	jmp	.L8
.L9:
	vaddsd	.LC0(%rip), %xmm0, %xmm0
	vmovsd	(%rdi), %xmm1
	movl	(%rsi), %eax
	addl	$1, %eax
	movl	%eax, (%rsi)
	leaq	8(%rdi), %rdi
.L8:
	vucomisd	%xmm1, %xmm0
	jp	.L7
	je	.L9
.L7:
	rep ret
	.cfi_endproc
.LFE25:
	.size	tfcmp3, .-tfcmp3
	.globl	tfcmp4
	.type	tfcmp4, @function
tfcmp4:
.LFB26:
	.cfi_startproc
	jmp	.L12
.L13:
	vaddsd	.LC0(%rip), %xmm0, %xmm0
	movl	(%rdi), %eax
	addl	$1, %eax
	movl	%eax, (%rdi)
.L12:
	vucomisd	%xmm1, %xmm0
	jnb	.L13
	rep ret
	.cfi_endproc
.LFE26:
	.size	tfcmp4, .-tfcmp4
	.globl	tfcmp5
	.type	tfcmp5, @function
tfcmp5:
.LFB27:
	.cfi_startproc
	jmp	.L15
.L16:
	vaddsd	.LC0(%rip), %xmm0, %xmm0
	movl	(%rdi), %eax
	addl	$1, %eax
	movl	%eax, (%rdi)
.L15:
	vucomisd	%xmm1, %xmm0
	ja	.L16
	rep ret
	.cfi_endproc
.LFE27:
	.size	tfcmp5, .-tfcmp5
	.globl	tlcmp
	.type	tlcmp, @function
tlcmp:
.LFB28:
	.cfi_startproc
	jmp	.L18
.L19:
	vxorpd	%xmm0, %xmm0, %xmm0
	vcvtsi2sdq	%rdi, %xmm0, %xmm0
	vaddsd	.LC0(%rip), %xmm0, %xmm0
	vcvttsd2siq	%xmm0, %rdi
	movl	(%rdx), %eax
	addl	$1, %eax
	movl	%eax, (%rdx)
.L18:
	movq	%rdi, %rax
	subq	%rsi, %rax
	testq	%rax, %rax
	jg	.L19
	rep ret
	.cfi_endproc
.LFE28:
	.size	tlcmp, .-tlcmp
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	0
	.long	1072693248
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
