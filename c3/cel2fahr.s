	.file	"cel2fahr.c"
	.text
	.globl	cel2fahr
	.type	cel2fahr, @function
cel2fahr:
.LFB23:
	.cfi_startproc
	vmulsd	.LC0(%rip), %xmm0, %xmm0
	vaddsd	.LC1(%rip), %xmm0, %xmm0
	ret
	.cfi_endproc
.LFE23:
	.size	cel2fahr, .-cel2fahr
	.section	.rodata.cst8,"aM",@progbits,8
	.align 8
.LC0:
	.long	3435973837
	.long	1073532108
	.align 8
.LC1:
	.long	0
	.long	1077936128
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
