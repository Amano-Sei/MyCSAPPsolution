	.file	"tmain.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	movl	$0, %eax
    movl    $0x12345678, %edi
    vpxor   %xmm0, %xmm0, %xmm0
    vpinsrd $0, %edi, %xmm0, %xmm1
    ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
