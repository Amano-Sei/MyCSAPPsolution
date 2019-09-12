	.file	"float_mov.c"
	.text
	.globl	float_mov
	.type	float_mov, @function
float_mov:
.LFB23:
	.cfi_startproc
	vmovss	(%rdi), %xmm1
	vmovss	%xmm0, (%rsi)
	vmovaps	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE23:
	.size	float_mov, .-float_mov
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
