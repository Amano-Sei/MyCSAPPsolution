	.file	"tests.c"
	.text
	.globl	u2f
	.type	u2f, @function
u2f:
.LFB19:
	.cfi_startproc
	flds	4(%esp)
	ret
	.cfi_endproc
.LFE19:
	.size	u2f, .-u2f
	.globl	f2u
	.type	f2u, @function
f2u:
.LFB20:
	.cfi_startproc
	movl	4(%esp), %eax
	ret
	.cfi_endproc
.LFE20:
	.size	f2u, .-f2u
	.globl	test_bitXor
	.type	test_bitXor, @function
test_bitXor:
.LFB21:
	.cfi_startproc
	movl	8(%esp), %eax
	xorl	4(%esp), %eax
	ret
	.cfi_endproc
.LFE21:
	.size	test_bitXor, .-test_bitXor
	.globl	test_tmin
	.type	test_tmin, @function
test_tmin:
.LFB22:
	.cfi_startproc
	movl	$-2147483648, %eax
	ret
	.cfi_endproc
.LFE22:
	.size	test_tmin, .-test_tmin
	.globl	test_isTmax
	.type	test_isTmax, @function
test_isTmax:
.LFB23:
	.cfi_startproc
	cmpl	$2147483647, 4(%esp)
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	test_isTmax, .-test_isTmax
	.globl	test_allOddBits
	.type	test_allOddBits, @function
test_allOddBits:
.LFB24:
	.cfi_startproc
	movl	4(%esp), %edx
	movl	%edx, %eax
	sarl	%eax
	andl	$1, %eax
	je	.L6
	movl	$3, %ecx
.L8:
	movl	%edx, %eax
	sarl	%cl, %eax
	andl	$1, %eax
	je	.L6
	addl	$2, %ecx
	cmpl	$33, %ecx
	jne	.L8
.L6:
	rep ret
	.cfi_endproc
.LFE24:
	.size	test_allOddBits, .-test_allOddBits
	.globl	test_negate
	.type	test_negate, @function
test_negate:
.LFB25:
	.cfi_startproc
	movl	4(%esp), %eax
	negl	%eax
	ret
	.cfi_endproc
.LFE25:
	.size	test_negate, .-test_negate
	.globl	test_isAsciiDigit
	.type	test_isAsciiDigit, @function
test_isAsciiDigit:
.LFB26:
	.cfi_startproc
	movl	4(%esp), %eax
	subl	$48, %eax
	cmpl	$9, %eax
	setbe	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE26:
	.size	test_isAsciiDigit, .-test_isAsciiDigit
	.globl	test_conditional
	.type	test_conditional, @function
test_conditional:
.LFB27:
	.cfi_startproc
	cmpl	$0, 4(%esp)
	movl	12(%esp), %eax
	cmovne	8(%esp), %eax
	ret
	.cfi_endproc
.LFE27:
	.size	test_conditional, .-test_conditional
	.globl	test_isLessOrEqual
	.type	test_isLessOrEqual, @function
test_isLessOrEqual:
.LFB28:
	.cfi_startproc
	movl	8(%esp), %eax
	cmpl	%eax, 4(%esp)
	setle	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE28:
	.size	test_isLessOrEqual, .-test_isLessOrEqual
	.globl	test_logicalNeg
	.type	test_logicalNeg, @function
test_logicalNeg:
.LFB29:
	.cfi_startproc
	cmpl	$0, 4(%esp)
	sete	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE29:
	.size	test_logicalNeg, .-test_logicalNeg
	.globl	test_howManyBits
	.type	test_howManyBits, @function
test_howManyBits:
.LFB30:
	.cfi_startproc
	movl	4(%esp), %eax
	cltd
	xorl	%edx, %eax
	movl	%eax, %edx
	testl	%eax, %eax
	je	.L19
	movl	$0, %eax
.L20:
	addl	$1, %eax
	shrl	%edx
	jne	.L20
.L19:
	addl	$1, %eax
	ret
	.cfi_endproc
.LFE30:
	.size	test_howManyBits, .-test_howManyBits
	.globl	test_floatScale2
	.type	test_floatScale2, @function
test_floatScale2:
.LFB31:
	.cfi_startproc
	subl	$4, %esp
	.cfi_def_cfa_offset 8
	movl	8(%esp), %eax
	movl	%eax, (%esp)
	flds	(%esp)
	fld	%st(0)
	fadd	%st(1), %st
	fstps	(%esp)
	fucomip	%st(0), %st
	cmovnp	(%esp), %eax
	addl	$4, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE31:
	.size	test_floatScale2, .-test_floatScale2
	.globl	test_floatFloat2Int
	.type	test_floatFloat2Int, @function
test_floatFloat2Int:
.LFB32:
	.cfi_startproc
	subl	$8, %esp
	.cfi_def_cfa_offset 12
	fnstcw	6(%esp)
	movzwl	6(%esp), %eax
	orb	$12, %ah
	movw	%ax, 4(%esp)
	flds	12(%esp)
	fldcw	4(%esp)
	fistpl	(%esp)
	fldcw	6(%esp)
	movl	(%esp), %eax
	addl	$8, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE32:
	.size	test_floatFloat2Int, .-test_floatFloat2Int
	.globl	test_floatPower2
	.type	test_floatPower2, @function
test_floatPower2:
.LFB33:
	.cfi_startproc
	subl	$4, %esp
	.cfi_def_cfa_offset 8
	call	__x86.get_pc_thunk.cx
	addl	$_GLOBAL_OFFSET_TABLE_, %ecx
	movl	8(%esp), %edx
	movl	$0, %eax
	cmpl	$-2147483648, %edx
	je	.L29
	flds	.LC0@GOTOFF(%ecx)
	testl	%edx, %edx
	js	.L40
.L31:
	testl	%edx, %edx
	jle	.L37
	fld1
	fstps	(%esp)
	jmp	.L34
.L40:
	fstp	%st(0)
	negl	%edx
	flds	.LC1@GOTOFF(%ecx)
	jmp	.L31
.L33:
	fmul	%st(0), %st
	sarl	%edx
	testl	%edx, %edx
	jle	.L41
.L34:
	testb	$1, %dl
	je	.L33
	flds	(%esp)
	fmul	%st(1), %st
	fstps	(%esp)
	jmp	.L33
.L37:
	fstp	%st(0)
	fld1
	fstps	(%esp)
	jmp	.L32
.L41:
	fstp	%st(0)
.L32:
	movl	(%esp), %eax
.L29:
	addl	$4, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
.LFE33:
	.size	test_floatPower2, .-test_floatPower2
	.section	.rodata.cst4,"aM",@progbits,4
	.align 4
.LC0:
	.long	1073741824
	.align 4
.LC1:
	.long	1056964608
	.section	.text.__x86.get_pc_thunk.cx,"axG",@progbits,__x86.get_pc_thunk.cx,comdat
	.globl	__x86.get_pc_thunk.cx
	.hidden	__x86.get_pc_thunk.cx
	.type	__x86.get_pc_thunk.cx, @function
__x86.get_pc_thunk.cx:
.LFB36:
	.cfi_startproc
	movl	(%esp), %ecx
	ret
	.cfi_endproc
.LFE36:
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
