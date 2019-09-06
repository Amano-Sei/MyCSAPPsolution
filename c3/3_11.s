	.file	"3_11.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB23:
	.cfi_startproc
    xorq    %rdx, %rdx
    xorl    %edx, %edx
    movq    $0, %rdx
    movl    $0, %edx
	ret
	.cfi_endproc
.LFE23:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits
