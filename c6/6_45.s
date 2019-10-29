	.file	"6_45.c"
	.text
	.globl	transpose
	.type	transpose, @function
transpose:
.LFB23:
	.cfi_startproc
	pushq	%r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	pushq	%r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	pushq	%r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	pushq	%rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	pushq	%rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	movl	$0, %ecx
	jmp	.L2
.L3:
	movl	%ecx, %r8d
	imull	%edx, %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	(%rsi,%r8,4), %r10d
	movl	4(%rsi,%r8,4), %r9d
	movl	8(%rsi,%r8,4), %r12d
	movl	12(%rsi,%r8,4), %r11d
	movl	%eax, %ebx
	imull	%edx, %ebx
	addl	%ecx, %ebx
	movslq	%ebx, %rbx
	movl	%r10d, (%rdi,%rbx,4)
	leal	1(%rax), %r10d
	imull	%edx, %r10d
	addl	%ecx, %r10d
	movslq	%r10d, %r10
	movl	%r9d, (%rdi,%r10,4)
	leal	2(%rax), %r9d
	imull	%edx, %r9d
	addl	%ecx, %r9d
	movslq	%r9d, %r9
	movl	%r12d, (%rdi,%r9,4)
	leal	3(%rax), %r8d
	imull	%edx, %r8d
	addl	%ecx, %r8d
	movslq	%r8d, %r8
	movl	%r11d, (%rdi,%r8,4)
	leal	1(%rcx), %r11d
	imull	%edx, %r11d
	addl	%eax, %r11d
	movslq	%r11d, %r11
	movl	(%rsi,%r11,4), %r14d
	movl	4(%rsi,%r11,4), %r13d
	movl	8(%rsi,%r11,4), %r12d
	movl	12(%rsi,%r11,4), %r11d
	movl	%r14d, 4(%rdi,%rbx,4)
	movl	%r13d, 4(%rdi,%r10,4)
	movl	%r12d, 4(%rdi,%r9,4)
	movl	%r11d, 4(%rdi,%r8,4)
	leal	2(%rcx), %r11d
	imull	%edx, %r11d
	addl	%eax, %r11d
	movslq	%r11d, %r11
	movl	(%rsi,%r11,4), %r14d
	movl	4(%rsi,%r11,4), %r13d
	movl	8(%rsi,%r11,4), %r12d
	movl	12(%rsi,%r11,4), %r11d
	movl	%r14d, 8(%rdi,%rbx,4)
	movl	%r13d, 8(%rdi,%r10,4)
	movl	%r12d, 8(%rdi,%r9,4)
	movl	%r11d, 8(%rdi,%r8,4)
	leal	3(%rcx), %r11d
	imull	%edx, %r11d
	addl	%eax, %r11d
	movslq	%r11d, %r11
	movl	(%rsi,%r11,4), %r14d
	movl	4(%rsi,%r11,4), %r13d
	movl	8(%rsi,%r11,4), %r12d
	movl	12(%rsi,%r11,4), %r11d
	movl	%r14d, 12(%rdi,%rbx,4)
	movl	%r13d, 12(%rdi,%r10,4)
	movl	%r12d, 12(%rdi,%r9,4)
	movl	%r11d, 12(%rdi,%r8,4)
	addl	$4, %eax
.L6:
	cmpl	%eax, %ebp
	jg	.L3
	jmp	.L4
.L5:
	movl	%ecx, %r8d
	imull	%edx, %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	(%rsi,%r8,4), %r10d
	leal	1(%rcx), %r8d
	imull	%edx, %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	(%rsi,%r8,4), %r9d
	leal	2(%rcx), %r8d
	imull	%edx, %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	(%rsi,%r8,4), %r11d
	leal	3(%rcx), %r8d
	imull	%edx, %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	(%rsi,%r8,4), %ebx
	movl	%eax, %r8d
	imull	%edx, %r8d
	addl	%ecx, %r8d
	movslq	%r8d, %r8
	movl	%r10d, (%rdi,%r8,4)
	movl	%r9d, 4(%rdi,%r8,4)
	movl	%r11d, 8(%rdi,%r8,4)
	movl	%ebx, 12(%rdi,%r8,4)
	addl	$1, %eax
.L4:
	cmpl	%edx, %eax
	jl	.L5
	addl	$4, %ecx
.L2:
	leal	-3(%rdx), %ebp
	cmpl	%ecx, %ebp
	jle	.L7
	movl	$0, %eax
	jmp	.L6
.L8:
	movl	%ecx, %r8d
	imull	%edx, %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	(%rsi,%r8,4), %ebx
	movl	4(%rsi,%r8,4), %r11d
	movl	8(%rsi,%r8,4), %r10d
	movl	12(%rsi,%r8,4), %r9d
	movl	%eax, %r8d
	imull	%edx, %r8d
	addl	%ecx, %r8d
	movslq	%r8d, %r8
	movl	%ebx, (%rdi,%r8,4)
	leal	1(%rax), %r8d
	imull	%edx, %r8d
	addl	%ecx, %r8d
	movslq	%r8d, %r8
	movl	%r11d, (%rdi,%r8,4)
	leal	2(%rax), %r8d
	imull	%edx, %r8d
	addl	%ecx, %r8d
	movslq	%r8d, %r8
	movl	%r10d, (%rdi,%r8,4)
	leal	3(%rax), %r8d
	imull	%edx, %r8d
	addl	%ecx, %r8d
	movslq	%r8d, %r8
	movl	%r9d, (%rdi,%r8,4)
	addl	$4, %eax
.L11:
	cmpl	%eax, %ebp
	jg	.L8
	jmp	.L9
.L10:
	movl	%ecx, %r9d
	imull	%edx, %r9d
	addl	%eax, %r9d
	movslq	%r9d, %r9
	movl	%eax, %r8d
	imull	%edx, %r8d
	addl	%ecx, %r8d
	movslq	%r8d, %r8
	movl	(%rsi,%r9,4), %r9d
	movl	%r9d, (%rdi,%r8,4)
	addl	$1, %eax
.L9:
	cmpl	%edx, %eax
	jl	.L10
	addl	$1, %ecx
.L7:
	cmpl	%edx, %ecx
	jge	.L15
	movl	$0, %eax
	jmp	.L11
.L15:
	popq	%rbx
	.cfi_def_cfa_offset 40
	popq	%rbp
	.cfi_def_cfa_offset 32
	popq	%r12
	.cfi_def_cfa_offset 24
	popq	%r13
	.cfi_def_cfa_offset 16
	popq	%r14
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE23:
	.size	transpose, .-transpose
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
