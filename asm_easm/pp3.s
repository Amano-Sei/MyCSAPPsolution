	.file	"pp3.c"
	.text
	.globl	lock_incr
	.type	lock_incr, @function
lock_incr:
.LFB23:
	.cfi_startproc
#APP
# 13 "pp3.c" 1
	lock
	addl $1, (%rdi)
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE23:
	.size	lock_incr, .-lock_incr
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
