	.file	"gets.c"
	.text
	.p2align 4,,15
	.globl	gets
	.type	gets, @function
gets:
.LFB23:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	movq	%rdi, %rbp
	movq	%rdi, %rbx
	subq	$8, %rsp
	.cfi_def_cfa_offset 32
	jmp	.L2
	.p2align 4,,10
	.p2align 3
.L3:
	cmpl	$-1, %eax
	je	.L9
	addq	$1, %rbx
	movb	%al, -1(%rbx)
.L2:
	movq	stdin(%rip), %rdi
	call	_IO_getc@PLT
	cmpl	$10, %eax
	jne	.L3
.L6:
	movb	$0, (%rbx)
	movq	%rbp, %rax
.L1:
	addq	$8, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L9:
	.cfi_restore_state
	cmpq	%rbp, %rbx
	jne	.L6
	xorl	%eax, %eax
	jmp	.L1
	.cfi_endproc
.LFE23:
	.size	gets, .-gets
	.p2align 4,,15
	.globl	echo
	.type	echo, @function
echo:
.LFB24:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movq	%rsp, %rbp
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movq	%rbp, %rbx
	jmp	.L11
	.p2align 4,,10
	.p2align 3
.L12:
	cmpl	$-1, %eax
	je	.L18
	addq	$1, %rbx
	movb	%al, -1(%rbx)
.L11:
	movq	stdin(%rip), %rdi
	call	_IO_getc@PLT
	cmpl	$10, %eax
	jne	.L12
.L15:
	movb	$0, (%rbx)
.L13:
	movq	%rbp, %rdi
	call	puts@PLT
	movq	8(%rsp), %rax
	xorq	%fs:40, %rax
	jne	.L19
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.p2align 4,,10
	.p2align 3
.L18:
	.cfi_restore_state
	cmpq	%rbp, %rbx
	jne	.L15
	jmp	.L13
.L19:
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE24:
	.size	echo, .-echo
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
