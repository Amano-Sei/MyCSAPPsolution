	.file	"tf2d.c"
	.text
	.globl	tf2d
	.type	tf2d, @function
tf2d:
.LFB23:
	.cfi_startproc
	vcvtss2sd	%xmm0, %xmm0, %xmm0
	ret
	.cfi_endproc
.LFE23:
	.size	tf2d, .-tf2d
	.globl	fd2f
	.type	fd2f, @function
fd2f:
.LFB24:
	.cfi_startproc
	vcvtsd2ss	%xmm0, %xmm0, %xmm0
	ret
	.cfi_endproc
.LFE24:
	.size	fd2f, .-fd2f
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
