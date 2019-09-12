	.file	"umult_ok.c"
	.text
	.globl	umult_ok
	.type	umult_ok, @function
umult_ok:
.LFB23:
	.cfi_startproc
	movq	%rdx, %rcx
#APP
# 13 "umult_ok.c" 1
	movq %rdi, %rax
	mulq %rsi
	movq %rax, (%rcx)
	setae %dil
# 0 "" 2
#NO_APP
	movzbl	%dil, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	umult_ok, .-umult_ok
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
