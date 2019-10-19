	.file	"twrongsize.c"
	.text
	.globl	test
	.type	test, @function
test:
.LFB23:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	imull	%esi, %edi
	movl	%edi, (%rdx)
#APP
# 13 "twrongsize.c" 1
	setae 4(%rsp) #看看注释还在么
# 0 "" 2
#NO_APP
	movl	4(%rsp), %eax
	movq	8(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L4
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L4:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE23:
	.size	test, .-test
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%x\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB24:
	.cfi_startproc
	subq	$24, %rsp
	.cfi_def_cfa_offset 32
	movq	%fs:40, %rax
	movq	%rax, 8(%rsp)
	xorl	%eax, %eax
	movl	$0, 4(%rsp)
	leaq	4(%rsp), %rdx
	movl	$2, %esi
	movl	$2, %edi
	call	test
	movl	%eax, %edx
	leaq	.LC0(%rip), %rsi
	movl	$1, %edi
	movl	$0, %eax
	call	__printf_chk@PLT
	movq	8(%rsp), %rcx
	xorq	%fs:40, %rcx
	jne	.L8
	movl	$0, %eax
	addq	$24, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 8
	ret
.L8:
	.cfi_restore_state
	call	__stack_chk_fail@PLT
	.cfi_endproc
.LFE24:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
