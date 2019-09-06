	.file	"tmov.c"
	.text
	.globl	tmov
	.type	tmov, @function
tmov:
.LFB23:
	.cfi_startproc
	movq	$-268435455, %rax
	ret
	.cfi_endproc
.LFE23:
	.size	tmov, .-tmov
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
