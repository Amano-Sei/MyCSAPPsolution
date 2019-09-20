0x000:                                      #.pos0
0x000:  30 f4 00 02 00 00 00 00 00 00       #   irmovq  stack, %rsp
0x00a:  80 38 00 00 00 00 00 00 00          #   call main
0x013:  00                                  #   halt

0x018:                                      #.align 8
0x018:  0d 00 0d 00 0d 00 00 00             #   .quad 0x000d000d000d
0x020:  c0 00 c0 00 c0 00 00 00             #   .quad 0x00c000c000c0
0x028:  00 0b 00 0b 00 0b 00 00             #   .quad 0x0b000b000b00
0x030:  00 a0 00 a0 00 a0 00 00             #   .quad 0xa000a000a000

0x038:                                      #main:
0x038:  30 f7 18 00 00 00 00 00 00 00       #   irmovq  array, %rdi
0x042:  30 f6 04 00 00 00 00 00 00 00       #   irmovq  $4, %rsi
0x04c:  80 56 00 00 00 00 00 00 00          #   call    sum
0x055:  90                                  #   ret

0x056:                                      #sum:
0x056:  30 f8 08 00 00 00 00 00 00 00       #   irmovq  $8, %r8
0x060:  30 f9 01 00 00 00 00 00 00 00       #   irmovq  $1, %9
0x06a:  63 00                               #   xorq    %rax, %rax
0x06c:  62 66                               #   andq    %rsi, %rsi
0x06e:  70 87 00 00 00 00 00 00 00          #   jmp     test
0x077:                                      #loop:
0x077:  50 a7 00 00 00 00 00 00 00 00       #   mrmovq  (%rdi), %r10
0x081:  60 a0                               #   addq    %r10, %rax
0x083:  60 87                               #   addq    %r8, %rdi
0x085:  61 96                               #   subq    %r9, %rsi
0x087:                                      #test:
0x087:  74 77 00 00 00 00 00 00 00          #   jne     loop
0x090:  90                                  #   ret

0x200:                                      #.pos 0x200
0x200:                                      #stack:

