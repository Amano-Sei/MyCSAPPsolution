	.file	"pp5.c"
	.text
	.globl	dmin
	.type	dmin, @function
dmin:
.LFB23:
	.cfi_startproc
#APP
# 12 "pp5.c" 1
	vminsd %xmm0, %xmm1, %xmm0
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE23:
	.size	dmin, .-dmin
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
