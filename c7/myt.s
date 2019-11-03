	.file	"myt.c"
	.text
	.globl	desu
	.type	desu, @function
desu:
.LFB0:
	.cfi_startproc
	movl	a.1801(%rip), %eax
	leal	1(%rax), %r8d
	movl	%r8d, a.1801(%rip)
	movl	b.1802(%rip), %eax
	addl	$1, %eax
	movl	%eax, b.1802(%rip)
	movl	c.1803(%rip), %ecx
	addl	$1, %ecx
	movl	%ecx, c.1803(%rip)
	addl	%r8d, %eax
	addl	%ecx, %eax
	addl	%edi, %eax
	addl	%esi, %eax
	addl	%edx, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	desu, .-desu
	.data
	.align 4
	.type	c.1803, @object
	.size	c.1803, 4
c.1803:
	.long	2
	.local	b.1802
	.comm	b.1802,4,4
	.local	a.1801
	.comm	a.1801,4,4
	.globl	c
	.align 4
	.type	c, @object
	.size	c, 4
c:
	.long	2
	.globl	b
	.bss
	.align 4
	.type	b, @object
	.size	b, 4
b:
	.zero	4
	.comm	a,4,4
	.globl	tdesu
	.data
	.align 8
	.type	tdesu, @object
	.size	tdesu, 12
tdesu:
	.long	1
	.long	2
	.long	3
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
