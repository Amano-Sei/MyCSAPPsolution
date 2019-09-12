	.file	"tmult_ok1.c"
	.text
	.globl	tmult_ok1
	.type	tmult_ok1, @function
tmult_ok1:
.LFB23:
	.cfi_startproc
	imulq	%rsi, %rdi
	movq	%rdi, (%rdx)
#APP
# 13 "tmult_ok1.c" 1
	setae %al
# 0 "" 2
#NO_APP
	movl	$0, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	tmult_ok1, .-tmult_ok1
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
