	.file	"pp6.c"
	.text
	.globl	dsqrt
	.type	dsqrt, @function
dsqrt:
.LFB23:
	.cfi_startproc
#APP
# 12 "pp6.c" 1
	sqrtsd %xmm0, %xmm0
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE23:
	.size	dsqrt, .-dsqrt
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
