.global find_range
find_range:
    vxorps %xmm1, %xmm1, %xmm1
    vucomiss %xmm1, %xmm0
    movl $0, %edi
    movl $1, %esi
    movl $2, %eax
    movl $3, %ecx
    cmovb %edi, %eax
    cmove %esi, %eax
#    cmova %edx, %eax
    cmovp %ecx, %eax
    ret
#论证了下，除了pf外，都可以通过提前存储在一个寄存器中一个结果减少一个指令
#虽然某dalao博主如是那样写，怕是没有测试（

