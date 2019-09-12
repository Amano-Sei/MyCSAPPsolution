	.file	"funct3.c"
	.text
	.globl	fing_range
	.type	fing_range, @function
fing_range:
.LFB23:
	.cfi_startproc
	vxorps	%xmm1, %xmm1, %xmm1
	vucomiss	%xmm0, %xmm1
	ja	.L5
	vucomiss	%xmm1, %xmm0
	jp	.L8
	je	.L6
.L8:
	vucomiss	.LC0(%rip), %xmm0
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
	.size	fing_range, .-fing_range
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	0
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
