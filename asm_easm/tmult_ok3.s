	.file	"tmult_ok3.c"
	.text
	.globl	tmult_ok3
	.type	tmult_ok3, @function
tmult_ok3:
.LFB23:
	.cfi_startproc
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
#APP
# 13 "tmult_ok3.c" 1
	setae %al
# 0 "" 2
#NO_APP
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	tmult_ok3, .-tmult_ok3
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
