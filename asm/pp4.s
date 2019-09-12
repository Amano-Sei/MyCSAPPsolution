	.file	"pp4.c"
	.text
	.globl	odd_parity
	.type	odd_parity, @function
odd_parity:
.LFB23:
	.cfi_startproc
	movl	$0, %eax
	jmp	.L2
.L3:
#APP
# 33 "pp4.c" 1
	testq %rdi, %rdi
	setnp %dl
# 0 "" 2
#NO_APP
	shrq	$8, %rdi
	movsbl	%dl, %edx
	xorl	%edx, %eax
.L2:
	testq	%rdi, %rdi
	jne	.L3
	rep ret
	.cfi_endproc
.LFE23:
	.size	odd_parity, .-odd_parity
	.globl	stans
	.type	stans, @function
stans:
.LFB24:
	.cfi_startproc
	movl	$0, %eax
	jmp	.L5
.L6:
#APP
# 48 "pp4.c" 1
	testb %dil, %dil
	setnp %dl
# 0 "" 2
#NO_APP
	movsbl	%dl, %edx
	xorl	%edx, %eax
	shrq	$8, %rdi
.L5:
	testq	%rdi, %rdi
	jne	.L6
	rep ret
	.cfi_endproc
.LFE24:
	.size	stans, .-stans
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%llx\n"
.LC1:
	.string	"%d %d\n"
.LC2:
	.string	"%d/... done...\n"
.LC3:
	.string	"\350\267\221\345\256\214\350\246\201\345\210\260n\345\271\264\345\220\216\344\272\206\345\231\227..."
	.text
	.globl	main
	.type	main, @function
main:
.LFB25:
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
	movl	$0, %ebx
	jmp	.L10
.L8:
	testl	$268435455, %ebx
	je	.L12
.L9:
	addq	$1, %rbx
	je	.L13
.L10:
	movq	%rbx, %rdi
	call	odd_parity
	movl	%eax, %ebp
	movq	%rbx, %rdi
	call	stans
	movl	%eax, %r12d
	cmpl	%eax, %ebp
	je	.L8
	movq	%rbx, %rdx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movl	%r12d, %ecx
	movl	%ebp, %edx
	leaq	.LC1(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	stdin(%rip), %rdi
	call	_IO_getc@PLT
	jmp	.L8
.L12:
	movq	%rbx, %rdx
	shrq	$28, %rdx
	leaq	.LC2(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	jmp	.L9
.L13:
	leaq	.LC3(%rip), %rdi
	call	puts@PLT
	movl	$0, %eax
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE25:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
