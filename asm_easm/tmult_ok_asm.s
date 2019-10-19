	.file	"tmult_ok_asm.c"
	.text
	.globl	tmult_ok_asm
	.type	tmult_ok_asm, @function
tmult_ok_asm:
.LFB23:
	.cfi_startproc
	imulq	%rdi, %rsi
	movq	%rsi, (%rdx)
#   testq	%rsi, %rsi
#   setg	%al
    setae   %al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE23:
	.size	tmult_ok_asm, .-tmult_ok_asm
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
