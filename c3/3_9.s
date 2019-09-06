	.file	"3_9.c"
	.text
	.globl	shift_left4_rightn
	.type	shift_left4_rightn, @function
shift_left4_rightn:
.LFB23:
	.cfi_startproc
	movq	%rdi, %rax
	salq	$4, %rax
	movl	%esi, %ecx
	sarq	%cl, %rax
	ret
	.cfi_endproc
.LFE23:
	.size	shift_left4_rightn, .-shift_left4_rightn
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
