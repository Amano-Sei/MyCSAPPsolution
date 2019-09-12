.global find_range

find_range:
    vxorps %xmm1, %xmm1, %xmm1
    vucomiss %xmm1, %xmm0
    jp .L4
    je .L2
    ja .L3
    movl $0, %eax
    ret
.L2:
    movl $1, %eax
    ret
.L3:
    movl $2, %eax
    ret
.L4:
    movl $3, %eax
    ret
#    movl $3, %eax
#    jp .L4
#    je .L2
#    ja .L3
#    subl $1, %eax
#.L2:
#    subl $1, %eax
#.L3:
#    subl $1, %eax
#.L4:
#    ret
#看了dalao的代码，虽然好像优雅了，但是实际上执行了更多的指令...
