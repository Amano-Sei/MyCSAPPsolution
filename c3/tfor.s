	.file	"tfor.c"
	.text
	.globl	tfor
	.type	tfor, @function
tfor:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -4(%rbp)
.L2:
	addl	$1, -4(%rbp)
	jmp	.L2
	.cfi_endproc
.LFE0:
	.size	tfor, .-tfor
	.globl	twhile
	.type	twhile, @function
twhile:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -4(%rbp)
.L4:
	addl	$1, -4(%rbp)
	jmp	.L4
	.cfi_endproc
.LFE1:
	.size	twhile, .-twhile
	.globl	tfortrue
	.type	tfortrue, @function
tfortrue:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, -4(%rbp)
.L6:
	addl	$1, -4(%rbp)
	jmp	.L6
	.cfi_endproc
.LFE2:
	.size	tfortrue, .-tfortrue
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
