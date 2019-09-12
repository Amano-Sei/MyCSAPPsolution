	.file	"pp2.c"
	.text
	.globl	umult_full
	.type	umult_full, @function
umult_full:
.LFB23:
	.cfi_startproc
	movq	%rdx, %rcx
#APP
# 11 "pp2.c" 1
	movq %rdi %rax
	mulq %rsi
	movq %rax (%rcx)
	movq %rdx 8(%rcx)
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE23:
	.size	umult_full, .-umult_full
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
