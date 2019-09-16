	.file	"tests.c"
	.text
	.globl	u2f
	.type	u2f, @function
u2f:
.LFB0:
	.cfi_startproc
	movl	%edi, -4(%rsp)
	movss	-4(%rsp), %xmm0
	ret
	.cfi_endproc
.LFE0:
	.size	u2f, .-u2f
	.globl	f2u
	.type	f2u, @function
f2u:
.LFB1:
	.cfi_startproc
	movd	%xmm0, %eax
	ret
	.cfi_endproc
.LFE1:
	.size	f2u, .-f2u
	.globl	test_bitXor
	.type	test_bitXor, @function
test_bitXor:
.LFB2:
	.cfi_startproc
	movl	%edi, %eax
	xorl	%esi, %eax
	ret
	.cfi_endproc
.LFE2:
	.size	test_bitXor, .-test_bitXor
	.globl	test_tmin
	.type	test_tmin, @function
test_tmin:
.LFB3:
	.cfi_startproc
	movl	$-2147483648, %eax
	ret
	.cfi_endproc
.LFE3:
	.size	test_tmin, .-test_tmin
	.globl	test_isTmax
	.type	test_isTmax, @function
test_isTmax:
.LFB4:
	.cfi_startproc
	cmpl	$2147483647, %edi
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE4:
	.size	test_isTmax, .-test_isTmax
	.globl	test_allOddBits
	.type	test_allOddBits, @function
test_allOddBits:
.LFB5:
	.cfi_startproc
	movl	%edi, %eax
	sarl	%eax
	andl	$1, %eax
	je	.L6
	movl	$3, %ecx
.L8:
	movl	%edi, %eax
	sarl	%cl, %eax
	andl	$1, %eax
	je	.L6
	addl	$2, %ecx
	cmpl	$33, %ecx
	jne	.L8
.L6:
	rep ret
	.cfi_endproc
.LFE5:
	.size	test_allOddBits, .-test_allOddBits
	.globl	test_negate
	.type	test_negate, @function
test_negate:
.LFB6:
	.cfi_startproc
	movl	%edi, %eax
	negl	%eax
	ret
	.cfi_endproc
.LFE6:
	.size	test_negate, .-test_negate
	.globl	test_isAsciiDigit
	.type	test_isAsciiDigit, @function
test_isAsciiDigit:
.LFB7:
	.cfi_startproc
	subl	$48, %edi
	cmpl	$9, %edi
	setbe	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE7:
	.size	test_isAsciiDigit, .-test_isAsciiDigit
	.globl	test_conditional
	.type	test_conditional, @function
test_conditional:
.LFB8:
	.cfi_startproc
	testl	%edi, %edi
	movl	%edx, %eax
	cmovne	%esi, %eax
	ret
	.cfi_endproc
.LFE8:
	.size	test_conditional, .-test_conditional
	.globl	test_isLessOrEqual
	.type	test_isLessOrEqual, @function
test_isLessOrEqual:
.LFB9:
	.cfi_startproc
	cmpl	%esi, %edi
	setle	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE9:
	.size	test_isLessOrEqual, .-test_isLessOrEqual
	.globl	test_logicalNeg
	.type	test_logicalNeg, @function
test_logicalNeg:
.LFB10:
	.cfi_startproc
	testl	%edi, %edi
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE10:
	.size	test_logicalNeg, .-test_logicalNeg
	.globl	test_howManyBits
	.type	test_howManyBits, @function
test_howManyBits:
.LFB11:
	.cfi_startproc
	movl	%edi, %eax
	sarl	$31, %eax
	xorl	%eax, %edi
	movl	%edi, %edx
	testl	%edi, %edi
	je	.L21
	movl	$0, %eax
.L20:
	addl	$1, %eax
	shrl	%edx
	jne	.L20
.L19:
	addl	$1, %eax
	ret
.L21:
	movl	%edi, %eax
	jmp	.L19
	.cfi_endproc
.LFE11:
	.size	test_howManyBits, .-test_howManyBits
	.globl	test_floatScale2
	.type	test_floatScale2, @function
test_floatScale2:
.LFB12:
	.cfi_startproc
	movl	%edi, -4(%rsp)
	movss	-4(%rsp), %xmm0
	movaps	%xmm0, %xmm1
	addss	%xmm0, %xmm1
	movd	%xmm1, %eax
	ucomiss	%xmm0, %xmm0
	cmovp	%edi, %eax
	ret
	.cfi_endproc
.LFE12:
	.size	test_floatScale2, .-test_floatScale2
	.globl	test_floatFloat2Int
	.type	test_floatFloat2Int, @function
test_floatFloat2Int:
.LFB13:
	.cfi_startproc
	movl	%edi, -4(%rsp)
	cvttss2si	-4(%rsp), %eax
	ret
	.cfi_endproc
.LFE13:
	.size	test_floatFloat2Int, .-test_floatFloat2Int
	.globl	test_floatPower2
	.type	test_floatPower2, @function
test_floatPower2:
.LFB14:
	.cfi_startproc
	movl	$0, %eax
	cmpl	$-2147483648, %edi
	je	.L27
	movss	.LC0(%rip), %xmm0
	testl	%edi, %edi
	js	.L37
.L29:
	testl	%edi, %edi
	jle	.L35
	movss	.LC2(%rip), %xmm1
	jmp	.L32
.L37:
	negl	%edi
	movss	.LC1(%rip), %xmm0
	jmp	.L29
.L31:
	mulss	%xmm0, %xmm0
	sarl	%edi
	testl	%edi, %edi
	jle	.L30
.L32:
	testb	$1, %dil
	je	.L31
	mulss	%xmm0, %xmm1
	jmp	.L31
.L35:
	movss	.LC2(%rip), %xmm1
.L30:
	movd	%xmm1, %eax
.L27:
	rep ret
	.cfi_endproc
.LFE14:
	.size	test_floatPower2, .-test_floatPower2
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1073741824
	.align 4
.LC1:
	.long	1056964608
	.align 4
.LC2:
	.long	1065353216
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
