#A:
0x100:  30 f3 fc ff ff ff ff ff ff ff   #   irmovq  $-4, %rbx
0x10a:  40 63 00 08 00 00 00 00 00 00   #   rmmovq  %rsi, 0x800(%rbx)
0x114:  00                              #   halt
                                        #见英文版勘误，额外加了一个00

#B:
0x200:  a0 6f                           #   pushq   %rsi
0x202:  80 0c 02 00 00 00 00 00 00      #   call    0x20c
0x20b:  00                              #   halt
0x20c:  30 f3 0a 00 00 00 00 00 00 00   #   irmovq  $10, %rbx
0x216:  90                              #   ret

#C:
0x300:  50 54 07 00 00 00 00 00 00 00   #   mrmovq  7(%rsp), %rbp
0x30a:  10                              #   nop
0x30b:  f0                              #unknow...
0x30c:  b0 1f                           #   popq    %rcx

#D:
0x400:  61 13                           #   subq    %rcx, %rbx
0x402:  73 00 04 00 00 00 00 00 00      #   je      0x400
0x40b:  00                              #   halt

#E:
0x500:  63 62                           #   xorq    %rsi, %rdx
0x502:  a0 f0                           #no such register...

