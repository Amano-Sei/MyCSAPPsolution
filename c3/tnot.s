	.file	"tnot.c"
	.text
	.globl	getnot
	.type	getnot, @function
getnot:
.LFB23:
	.cfi_startproc
	testl	%edi, %edi
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	getnot, .-getnot
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
