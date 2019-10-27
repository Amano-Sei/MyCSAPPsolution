	.file	"6_46.c"
	.text
	.globl	naive_col_convert
	.type	naive_col_convert, @function
naive_col_convert:
.LFB23:
	.cfi_startproc
	movl	$0, %r8d
	jmp	.L2
.L6:
	movl	$1, %ecx
.L3:
	movl	%ecx, (%rax)
	addl	$1, %edx
.L5:
	cmpl	%esi, %edx
	jge	.L8
	movl	%edx, %eax
	imull	%esi, %eax
	addl	%r8d, %eax
	cltq
	leaq	(%rdi,%rax,4), %rax
	cmpl	$0, (%rax)
	jne	.L6
	movl	%r8d, %ecx
	imull	%esi, %ecx
	addl	%edx, %ecx
	movslq	%ecx, %rcx
	movl	(%rdi,%rcx,4), %ecx
	testl	%ecx, %ecx
	je	.L3
	movl	$1, %ecx
	jmp	.L3
.L8:
	addl	$1, %r8d
.L2:
	cmpl	%esi, %r8d
	jge	.L9
	movl	$0, %edx
	jmp	.L5
.L9:
	rep ret
	.cfi_endproc
.LFE23:
	.size	naive_col_convert, .-naive_col_convert
	.globl	my_col_convert
	.type	my_col_convert, @function
my_col_convert:
.LFB24:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	movq	%rdi, %r10
	movl	$0, %r9d
	movl	%r9d, -28(%rsp)
	movl	%esi, %r15d
	jmp	.L11
.L52:
	movl	$1, %r8d
.L12:
	testl	%esi, %esi
	jne	.L53
	leal	1(%r15), %esi
	imull	-28(%rsp), %esi
	movslq	%esi, %rsi
	movl	8(%r10,%rsi,4), %edi
	testl	%edi, %edi
	je	.L13
	movl	$1, %edi
	jmp	.L13
.L53:
	movl	$1, %edi
.L13:
	testl	%ecx, %ecx
	jne	.L54
	leal	1(%r15), %ecx
	imull	-28(%rsp), %ecx
	movslq	%ecx, %rcx
	movl	12(%r10,%rcx,4), %esi
	testl	%esi, %esi
	je	.L14
	movl	$1, %esi
	jmp	.L14
.L54:
	movl	$1, %esi
.L14:
	testl	%edx, %edx
	jne	.L55
	leal	1(%r15), %edx
	imull	-28(%rsp), %edx
	movslq	%edx, %rdx
	movl	16(%r10,%rdx,4), %ecx
	testl	%ecx, %ecx
	je	.L15
	movl	$1, %ecx
	jmp	.L15
.L55:
	movl	$1, %ecx
.L15:
	leal	1(%r15), %edx
	imull	-28(%rsp), %edx
	movslq	%edx, %rdx
	movl	%r8d, 4(%r10,%rdx,4)
	movl	%edi, 8(%r10,%rdx,4)
	movl	%esi, 12(%r10,%rdx,4)
	movl	%ecx, 16(%r10,%rdx,4)
	movl	%r8d, (%r11)
	movl	%edi, (%rbx)
	movl	%esi, (%r14)
	movl	%ecx, (%r9)
	leaq	12(%r10,%r13,4), %rbx
	leaq	4(%r10,%rbp,4), %r11
	movl	(%r11), %esi
	leaq	4(%r10,%r12,4), %r9
	movl	(%r9), %ecx
	leaq	4(%r10,%r13,4), %r8
	movl	(%r8), %edx
	cmpl	$0, (%rbx)
	jne	.L56
	movl	16(%r10,%r12,4), %edi
	testl	%edi, %edi
	je	.L16
	movl	$1, %edi
	jmp	.L16
.L56:
	movl	$1, %edi
.L16:
	testl	%esi, %esi
	jne	.L57
	movl	8(%r10,%rax,4), %esi
	testl	%esi, %esi
	je	.L17
	movl	$1, %esi
	jmp	.L17
.L57:
	movl	$1, %esi
.L17:
	testl	%ecx, %ecx
	jne	.L58
	movl	12(%r10,%rax,4), %ecx
	testl	%ecx, %ecx
	je	.L18
	movl	$1, %ecx
	jmp	.L18
.L58:
	movl	$1, %ecx
.L18:
	testl	%edx, %edx
	jne	.L59
	movl	16(%r10,%rax,4), %edx
	testl	%edx, %edx
	je	.L19
	movl	$1, %edx
	jmp	.L19
.L59:
	movl	$1, %edx
.L19:
	movl	%edi, 16(%r10,%r12,4)
	movl	%esi, 8(%r10,%rax,4)
	movl	%ecx, 12(%r10,%rax,4)
	movl	%edx, 16(%r10,%rax,4)
	movl	%edi, (%rbx)
	movl	%esi, (%r11)
	movl	%ecx, (%r9)
	movl	%edx, (%r8)
	leaq	8(%r10,%r12,4), %rsi
	leaq	8(%r10,%r13,4), %rcx
	movl	(%rcx), %eax
	cmpl	$0, (%rsi)
	jne	.L60
	movl	12(%r10,%rbp,4), %edx
	testl	%edx, %edx
	je	.L20
	movl	$1, %edx
	jmp	.L20
.L60:
	movl	$1, %edx
.L20:
	testl	%eax, %eax
	jne	.L61
	movl	16(%r10,%rbp,4), %eax
	testl	%eax, %eax
	je	.L21
	movl	$1, %eax
	jmp	.L21
.L61:
	movl	$1, %eax
.L21:
	movl	%edx, 12(%r10,%rbp,4)
	movl	%eax, 16(%r10,%rbp,4)
	movl	%edx, (%rsi)
	movl	%eax, (%rcx)
	movl	-28(%rsp), %eax
	addl	$5, %eax
	jmp	.L22
.L62:
	movl	$1, %ebx
.L23:
	testl	%r9d, %r9d
	jne	.L63
	movl	-28(%rsp), %r9d
	imull	%r15d, %r9d
	addl	%eax, %r9d
	movslq	%r9d, %r9
	movl	4(%r10,%r9,4), %r11d
	testl	%r11d, %r11d
	je	.L24
	movl	$1, %r11d
	jmp	.L24
.L63:
	movl	$1, %r11d
.L24:
	testl	%r8d, %r8d
	jne	.L64
	movl	-28(%rsp), %r8d
	imull	%r15d, %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	8(%r10,%r8,4), %r9d
	testl	%r9d, %r9d
	je	.L25
	movl	$1, %r9d
	jmp	.L25
.L64:
	movl	$1, %r9d
.L25:
	testl	%edi, %edi
	jne	.L65
	movl	-28(%rsp), %edi
	imull	%r15d, %edi
	addl	%eax, %edi
	movslq	%edi, %rdi
	movl	12(%r10,%rdi,4), %r8d
	testl	%r8d, %r8d
	je	.L26
	movl	$1, %r8d
	jmp	.L26
.L65:
	movl	$1, %r8d
.L26:
	movl	-28(%rsp), %edi
	imull	%r15d, %edi
	addl	%eax, %edi
	movslq	%edi, %rdi
	movl	%ebx, (%r10,%rdi,4)
	movl	%r11d, 4(%r10,%rdi,4)
	movl	%r9d, 8(%r10,%rdi,4)
	movl	%r8d, 12(%r10,%rdi,4)
	movl	%ebx, (%r14)
	movl	%r11d, 0(%r13)
	movl	%r9d, (%r12)
	movl	%r8d, 0(%rbp)
	leaq	4(%r10,%rsi,4), %r14
	leaq	4(%r10,%rcx,4), %r13
	movl	0(%r13), %r9d
	movq	-24(%rsp), %rbx
	leaq	4(%r10,%rbx,4), %r12
	movl	(%r12), %r8d
	leaq	4(%r10,%rdx,4), %rbp
	movl	0(%rbp), %edi
	cmpl	$0, (%r14)
	jne	.L66
	movl	-16(%rsp), %ebx
	leal	(%rbx,%rax), %r11d
	movslq	%r11d, %r11
	movl	(%r10,%r11,4), %ebx
	testl	%ebx, %ebx
	je	.L27
	movl	$1, %ebx
	jmp	.L27
.L66:
	movl	$1, %ebx
.L27:
	testl	%r9d, %r9d
	jne	.L67
	movl	-16(%rsp), %r11d
	leal	(%r11,%rax), %r9d
	movslq	%r9d, %r9
	movl	4(%r10,%r9,4), %r11d
	testl	%r11d, %r11d
	je	.L28
	movl	$1, %r11d
	jmp	.L28
.L67:
	movl	$1, %r11d
.L28:
	testl	%r8d, %r8d
	jne	.L68
	movl	-16(%rsp), %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	8(%r10,%r8,4), %r9d
	testl	%r9d, %r9d
	je	.L29
	movl	$1, %r9d
	jmp	.L29
.L68:
	movl	$1, %r9d
.L29:
	testl	%edi, %edi
	jne	.L69
	movl	-16(%rsp), %edi
	addl	%eax, %edi
	movslq	%edi, %rdi
	movl	12(%r10,%rdi,4), %r8d
	testl	%r8d, %r8d
	je	.L30
	movl	$1, %r8d
	jmp	.L30
.L69:
	movl	$1, %r8d
.L30:
	movl	-16(%rsp), %edi
	addl	%eax, %edi
	movslq	%edi, %rdi
	movl	%ebx, (%r10,%rdi,4)
	movl	%r11d, 4(%r10,%rdi,4)
	movl	%r9d, 8(%r10,%rdi,4)
	movl	%r8d, 12(%r10,%rdi,4)
	movl	%ebx, (%r14)
	movl	%r11d, 0(%r13)
	movl	%r9d, (%r12)
	movl	%r8d, 0(%rbp)
	leaq	8(%r10,%rsi,4), %r14
	leaq	8(%r10,%rcx,4), %r13
	movl	0(%r13), %r9d
	movq	-24(%rsp), %rbx
	leaq	8(%r10,%rbx,4), %r12
	movl	(%r12), %r8d
	leaq	8(%r10,%rdx,4), %rbp
	movl	0(%rbp), %edi
	cmpl	$0, (%r14)
	jne	.L70
	movl	-12(%rsp), %ebx
	leal	(%rbx,%rax), %r11d
	movslq	%r11d, %r11
	movl	(%r10,%r11,4), %ebx
	testl	%ebx, %ebx
	je	.L31
	movl	$1, %ebx
	jmp	.L31
.L70:
	movl	$1, %ebx
.L31:
	testl	%r9d, %r9d
	jne	.L71
	movl	-12(%rsp), %r11d
	leal	(%r11,%rax), %r9d
	movslq	%r9d, %r9
	movl	4(%r10,%r9,4), %r11d
	testl	%r11d, %r11d
	je	.L32
	movl	$1, %r11d
	jmp	.L32
.L71:
	movl	$1, %r11d
.L32:
	testl	%r8d, %r8d
	jne	.L72
	movl	-12(%rsp), %r8d
	addl	%eax, %r8d
	movslq	%r8d, %r8
	movl	8(%r10,%r8,4), %r9d
	testl	%r9d, %r9d
	je	.L33
	movl	$1, %r9d
	jmp	.L33
.L72:
	movl	$1, %r9d
.L33:
	testl	%edi, %edi
	jne	.L73
	movl	-12(%rsp), %edi
	addl	%eax, %edi
	movslq	%edi, %rdi
	movl	12(%r10,%rdi,4), %r8d
	testl	%r8d, %r8d
	je	.L34
	movl	$1, %r8d
	jmp	.L34
.L73:
	movl	$1, %r8d
.L34:
	movl	-12(%rsp), %edi
	addl	%eax, %edi
	movslq	%edi, %rdi
	movl	%ebx, (%r10,%rdi,4)
	movl	%r11d, 4(%r10,%rdi,4)
	movl	%r9d, 8(%r10,%rdi,4)
	movl	%r8d, 12(%r10,%rdi,4)
	movl	%ebx, (%r14)
	movl	%r11d, 0(%r13)
	movl	%r9d, (%r12)
	movl	%r8d, 0(%rbp)
	leaq	12(%r10,%rsi,4), %r9
	leaq	12(%r10,%rcx,4), %r11
	movl	(%r11), %ecx
	movq	-24(%rsp), %rsi
	leaq	12(%r10,%rsi,4), %r8
	movl	(%r8), %ebx
	leaq	12(%r10,%rdx,4), %rdi
	movl	(%rdi), %edx
	cmpl	$0, (%r9)
	jne	.L74
	movl	-8(%rsp), %esi
	addl	%eax, %esi
	movslq	%esi, %rsi
	movl	(%r10,%rsi,4), %esi
	testl	%esi, %esi
	je	.L35
	movl	$1, %esi
	jmp	.L35
.L74:
	movl	$1, %esi
.L35:
	testl	%ecx, %ecx
	jne	.L75
	movl	-8(%rsp), %ecx
	addl	%eax, %ecx
	movslq	%ecx, %rcx
	movl	4(%r10,%rcx,4), %ecx
	testl	%ecx, %ecx
	je	.L36
	movl	$1, %ecx
	jmp	.L36
.L75:
	movl	$1, %ecx
.L36:
	testl	%ebx, %ebx
	jne	.L76
	movl	-8(%rsp), %ebx
	addl	%eax, %ebx
	movslq	%ebx, %rbx
	movl	8(%r10,%rbx,4), %ebx
	testl	%ebx, %ebx
	je	.L37
	movl	$1, %ebx
	jmp	.L37
.L76:
	movl	$1, %ebx
.L37:
	testl	%edx, %edx
	jne	.L77
	movl	-8(%rsp), %edx
	addl	%eax, %edx
	movslq	%edx, %rdx
	movl	12(%r10,%rdx,4), %ebp
	testl	%ebp, %ebp
	je	.L38
	movl	$1, %ebp
	jmp	.L38
.L77:
	movl	$1, %ebp
.L38:
	movl	-8(%rsp), %edx
	addl	%eax, %edx
	movslq	%edx, %rdx
	movl	%esi, (%r10,%rdx,4)
	movl	%ecx, 4(%r10,%rdx,4)
	movl	%ebx, 8(%r10,%rdx,4)
	movl	%ebp, 12(%r10,%rdx,4)
	movl	%esi, (%r9)
	movl	%ecx, (%r11)
	movl	%ebx, (%r8)
	movl	%ebp, (%rdi)
	addl	$4, %eax
.L22:
	leal	-3(%r15), %edx
	cmpl	%eax, %edx
	jle	.L84
	movl	%eax, %esi
	imull	%r15d, %esi
	movl	-28(%rsp), %ebx
	addl	%ebx, %esi
	movslq	%esi, %rsi
	leaq	(%r10,%rsi,4), %r14
	leal	1(%rax), %ecx
	imull	%r15d, %ecx
	addl	%ebx, %ecx
	movslq	%ecx, %rcx
	leaq	(%r10,%rcx,4), %r13
	movl	0(%r13), %r9d
	leal	2(%rax), %edx
	imull	%r15d, %edx
	addl	%ebx, %edx
	movslq	%edx, %rdi
	movq	%rdi, -24(%rsp)
	leaq	(%r10,%rdi,4), %r12
	movl	(%r12), %r8d
	leal	3(%rax), %edx
	imull	%r15d, %edx
	addl	%ebx, %edx
	movslq	%edx, %rdx
	leaq	(%r10,%rdx,4), %rbp
	movl	0(%rbp), %edi
	cmpl	$0, (%r14)
	jne	.L62
	imull	%r15d, %ebx
	movl	%ebx, %r11d
	addl	%eax, %r11d
	movslq	%r11d, %r11
	movl	(%r10,%r11,4), %ebx
	testl	%ebx, %ebx
	je	.L23
	movl	$1, %ebx
	jmp	.L23
.L84:
	movl	-16(%rsp), %edi
	movl	-12(%rsp), %r8d
	movl	-8(%rsp), %r9d
	movl	-28(%rsp), %ecx
	jmp	.L40
.L78:
	movl	$1, %ebx
.L41:
	testl	%r11d, %r11d
	jne	.L79
	movl	%eax, %edx
	imull	%r15d, %edx
	addl	%ecx, %edx
	movslq	%edx, %rdx
	movl	4(%r10,%rdx,4), %r11d
	testl	%r11d, %r11d
	je	.L42
	movl	$1, %r11d
	jmp	.L42
.L79:
	movl	$1, %r11d
.L42:
	testl	%r12d, %r12d
	jne	.L80
	movl	%eax, %edx
	imull	%r15d, %edx
	addl	%ecx, %edx
	movslq	%edx, %rdx
	movl	8(%r10,%rdx,4), %esi
	testl	%esi, %esi
	je	.L43
	movl	$1, %esi
	jmp	.L43
.L80:
	movl	$1, %esi
.L43:
	testl	%ebp, %ebp
	jne	.L81
	movl	%eax, %edx
	imull	%r15d, %edx
	addl	%ecx, %edx
	movslq	%edx, %rdx
	movl	12(%r10,%rdx,4), %ebp
	testl	%ebp, %ebp
	je	.L44
	movl	$1, %ebp
	jmp	.L44
.L81:
	movl	$1, %ebp
.L44:
	movl	%eax, %edx
	imull	%r15d, %edx
	addl	%ecx, %edx
	movslq	%edx, %rdx
	movl	%ebx, (%r10,%rdx,4)
	movl	%r11d, 4(%r10,%rdx,4)
	movl	%esi, 8(%r10,%rdx,4)
	movl	%ebp, 12(%r10,%rdx,4)
	addl	$1, %eax
.L40:
	cmpl	%r15d, %eax
	jge	.L85
	movl	%ecx, %edx
	imull	%r15d, %edx
	addl	%eax, %edx
	movslq	%edx, %rdx
	leal	(%rdi,%rax), %esi
	movslq	%esi, %rsi
	movl	(%r10,%rsi,4), %r11d
	leal	(%r8,%rax), %esi
	movslq	%esi, %rsi
	movl	(%r10,%rsi,4), %r12d
	leal	(%r9,%rax), %esi
	movslq	%esi, %rsi
	movl	(%r10,%rsi,4), %ebp
	cmpl	$0, (%r10,%rdx,4)
	jne	.L78
	movl	%eax, %edx
	imull	%r15d, %edx
	addl	%ecx, %edx
	movslq	%edx, %rdx
	movl	(%r10,%rdx,4), %ebx
	testl	%ebx, %ebx
	je	.L41
	movl	$1, %ebx
	jmp	.L41
.L85:
	movl	-4(%rsp), %eax
	movl	%eax, -28(%rsp)
.L11:
	leal	-4(%r15), %eax
	cmpl	-28(%rsp), %eax
	jle	.L86
	movl	-28(%rsp), %r8d
	leal	1(%r8), %eax
	imull	%r15d, %eax
	movl	%eax, -16(%rsp)
	addl	%r8d, %eax
	cltq
	leaq	(%r10,%rax,4), %r11
	leal	2(%r8), %edx
	imull	%r15d, %edx
	movl	%edx, -12(%rsp)
	movl	%edx, %ebp
	addl	%r8d, %ebp
	movslq	%ebp, %rbp
	leaq	(%r10,%rbp,4), %rbx
	movl	(%rbx), %esi
	leal	3(%r8), %edx
	imull	%r15d, %edx
	movl	%edx, -8(%rsp)
	movl	%edx, %r12d
	addl	%r8d, %r12d
	movslq	%r12d, %r12
	leaq	(%r10,%r12,4), %r14
	movl	(%r14), %ecx
	leal	4(%r8), %edx
	movl	%edx, -4(%rsp)
	movl	%edx, %r13d
	imull	%r15d, %r13d
	addl	%r8d, %r13d
	movslq	%r13d, %r13
	leaq	(%r10,%r13,4), %r9
	movl	(%r9), %edx
	cmpl	$0, (%r11)
	jne	.L52
	leal	1(%r15), %edi
	imull	%r8d, %edi
	movslq	%edi, %rdi
	movl	4(%r10,%rdi,4), %r8d
	testl	%r8d, %r8d
	je	.L12
	movl	$1, %r8d
	jmp	.L12
.L86:
	movl	-28(%rsp), %r9d
	movl	%r15d, %r11d
.L47:
	leal	-1(%r11), %eax
	cmpl	%r9d, %eax
	jle	.L87
	leal	1(%r9), %edx
	jmp	.L48
.L82:
	movl	$1, %ecx
.L49:
	movl	%edx, %eax
	imull	%r11d, %eax
	addl	%r9d, %eax
	cltq
	movl	%ecx, (%r10,%rax,4)
	movl	%ecx, (%rsi)
	addl	$1, %edx
.L48:
	cmpl	%r11d, %edx
	jge	.L47
	movl	%r9d, %eax
	imull	%r11d, %eax
	addl	%edx, %eax
	cltq
	leaq	(%r10,%rax,4), %rsi
	cmpl	$0, (%rsi)
	jne	.L82
	movl	%edx, %eax
	imull	%r11d, %eax
	addl	%r9d, %eax
	cltq
	movl	(%r10,%rax,4), %ecx
	testl	%ecx, %ecx
	je	.L49
	movl	$1, %ecx
	jmp	.L49
.L87:
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE24:
	.size	my_col_convert, .-my_col_convert
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
