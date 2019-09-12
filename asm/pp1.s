	.file	"pp1.c"
	.text
	.p2align 4,,15
	.globl	tmult_ok
	.type	tmult_ok, @function
tmult_ok:
.LFB23:
	.cfi_startproc
#APP
# 12 "pp1.c" 1
	imulq %rdi, %rsi
	setae %dil
# 0 "" 2
#NO_APP
	movq	%rsi, (%rdx)
	movzbl	%dil, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	tmult_ok, .-tmult_ok
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
