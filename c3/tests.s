	.file	"tests.c"
	.text
	.globl	testo
	.type	testo, @function
testo:
.LFB23:
	.cfi_startproc
	addl	%esi, %edi
	addl	%edi, %edx
	addl	%edx, %ecx
	addl	%r8d, %ecx
	leal	(%rcx,%r9), %eax
	addl	8(%rsp), %eax
	addl	16(%rsp), %eax
	addl	24(%rsp), %eax
	ret
	.cfi_endproc
.LFE23:
	.size	testo, .-testo
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
