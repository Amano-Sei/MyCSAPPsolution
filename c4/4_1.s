0x100:  30 f3 0f 00 00 00 00 00 00 00   #   irmovq  $15, %rbx
0x10a:  20 31                           #   rrmovq  %rbx, %rcx
0x10c:                                  #loop:
0x10c:  40 13 fd ff ff ff ff ff ff ff   #   rmmovq  %rcx, -3(%rbx)
0x116:  60 31                           #   addq    %rbx, %rcx
0x118:  70 0c 01 00 00 00 00 00 00      #   jmp     loop

