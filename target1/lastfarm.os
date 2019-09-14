
lastfarm.o：     文件格式 elf64-x86-64


Disassembly of section .text:

0000000000000000 <.text>:
   0:	48 83 e8 01          	sub    $0x1,%rax
   4:	48 83 c0 01          	add    $0x1,%rax
   8:	48 83 f0 01          	xor    $0x1,%rax
   c:	48 83 c8 01          	or     $0x1,%rax
  10:	48 29 c0             	sub    %rax,%rax
  13:	48 01 c0             	add    %rax,%rax
  16:	48 31 c0             	xor    %rax,%rax
  19:	08 c0                	or     %al,%al
  1b:	40 08 ce             	or     %cl,%sil
  1e:	66 58                	pop    %ax
  20:	58                   	pop    %rax
