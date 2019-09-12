	.file	"3_56.c"
	.text
	.globl	a
	.type	a, @function
a:
.LFB23:
	.cfi_startproc
	vandpd	.LC0(%rip), %xmm0, %xmm0
	ret
	.cfi_endproc
.LFE23:
	.size	a, .-a
	.globl	b
	.type	b, @function
b:
.LFB24:
	.cfi_startproc
	vxorpd	%xmm0, %xmm0, %xmm0
	ret
	.cfi_endproc
.LFE24:
	.size	b, .-b
	.globl	c
	.type	c, @function
c:
.LFB25:
	.cfi_startproc
	vxorpd	.LC2(%rip), %xmm0, %xmm0
	ret
	.cfi_endproc
.LFE25:
	.size	c, .-c
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	4294967295
	.long	2147483647
	.long	0
	.long	0
	.align 16
.LC2:
	.long	0
	.long	-2147483648
	.long	0
	.long	0
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
