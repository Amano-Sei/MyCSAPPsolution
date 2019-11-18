	.file	"tfork.c"
	.text
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"fork error: %s\n"
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC1:
	.string	"child?: x = %d, y = %d, with id %d %d\n"
	.align 8
.LC2:
	.string	"parent?: x = %d, y = %d , with id %d %d\n"
	.section	.rodata.str1.1
.LC3:
	.string	"%d====\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB63:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	call	fork@PLT
	testl	%eax, %eax
	js	.L13
	testl	%eax, %eax
	je	.L11
	movl	$0, %ebp
	movl	$1, %ebx
	jmp	.L4
.L13:
	call	__errno_location@PLT
	movl	(%rax), %edi
	call	strerror@PLT
	movq	%rax, %rcx
	leaq	.LC0(%rip), %rdx
	movl	$1, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	__fprintf_chk@PLT
	movl	$0, %edi
	call	exit@PLT
.L5:
	call	getppid@PLT
	movl	%eax, %r12d
	call	getpid@PLT
	movl	%eax, %r8d
	addl	$1, %ebx
	movl	x(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, x(%rip)
	movl	%r12d, %r9d
	movl	%ebx, %ecx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addl	$1, %ebp
.L3:
	cmpl	$99, %ebp
	jle	.L5
.L6:
	call	getpid@PLT
	movl	%eax, %edx
	leaq	.LC3(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	call	fork@PLT
	testl	%eax, %eax
	js	.L14
	testl	%eax, %eax
	jne	.L9
	call	getppid@PLT
	movl	%eax, %ebp
	call	getpid@PLT
	movl	%eax, %r8d
	leal	1(%rbx), %ecx
	movl	x(%rip), %eax
	leal	1(%rax), %edx
	movl	%edx, x(%rip)
	movl	%ebp, %r9d
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
.L10:
	movl	$0, %edi
	call	exit@PLT
.L11:
	movl	$0, %ebp
	movl	$1, %ebx
	jmp	.L3
.L7:
	call	getppid@PLT
	movl	%eax, %r12d
	call	getpid@PLT
	movl	%eax, %r8d
	subl	$1, %ebx
	movl	x(%rip), %eax
	leal	-1(%rax), %edx
	movl	%edx, x(%rip)
	movl	%r12d, %r9d
	movl	%ebx, %ecx
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	addl	$1, %ebp
.L4:
	cmpl	$99, %ebp
	jle	.L7
	jmp	.L6
.L14:
	call	__errno_location@PLT
	movl	(%rax), %edi
	call	strerror@PLT
	movq	%rax, %rcx
	leaq	.LC0(%rip), %rdx
	movl	$1, %esi
	movq	stderr(%rip), %rdi
	movl	$0, %eax
	call	__fprintf_chk@PLT
	movl	$0, %edi
	call	exit@PLT
.L9:
	call	getppid@PLT
	movl	%eax, %ebp
	call	getpid@PLT
	movl	%eax, %r8d
	leal	-1(%rbx), %ecx
	movl	x(%rip), %eax
	leal	-1(%rax), %edx
	movl	%edx, x(%rip)
	movl	%ebp, %r9d
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	jmp	.L10
	.cfi_endproc
.LFE63:
	.size	main, .-main
	.globl	x
	.data
	.align 4
	.type	x, @object
	.size	x, 4
x:
	.long	1
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
