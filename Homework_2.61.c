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

#include <stdio.h>



int main()
{
	int x = 0;
	// int x = 1;
	// int x = 0xFF;
	// int x = 0xFF << ((sizeof(int) - 1) * 8);

	printf("x = 0x%x\n\n", x);

	// 	Logic operators take their arguments as true if non-zero, and
	// return 0 or 1.
	printf("A: %d\n", !!x);

	// 	-1 is the only number that has no bit equals 0 in its two's
	// complement representation.
	printf("B: %d\n", !!(x + 1));

	printf("C: %d\n", !!(x & 0xFF));

	// 	Arithmetic right shift will make the result all 1 when the
	// most significant byte contains no 0 i.e. all 1. And then it's -1
	// again.
	printf("D: %d\n", !!((x >> ((sizeof(int) - 1) << 3)) + 1));


	return 0;
}
