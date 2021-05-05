/* A homework problem solution for the CS:APP3e

   Copyright (C) 2021 Tongjie Liu <tongjieandliu@gmail.com>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

/*
	A. x: %rdi
	   n: %ecx
	   result: %rax
	   mask: %rdx


	B. result = 0
	   mask = 1


	C. mask != 0


	D. mask <<= n


	E. result |= (x & mask); 
 */

// F.
long loop(long x, int n)
{
	long result = 0;
	long mask;

	for (mask = 1; mask != 0; mask <<= n)
		result |= (x & mask);

	return result;
}
