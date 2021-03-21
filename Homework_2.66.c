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



int leftmost_one(unsigned int x)
{
	unsigned int shifted;

	// 	Let bit k be the bit which has the leftmost 1, when x is not
	// equal to 0. Then, the bit k - 1 of the variable shifted will be 1.
	shifted = x >> 1;
	// 	After this, x has at least two 1s in bit k and bit k - 1 if
	// k > 0 or k = 0.
	x = x | shifted;

	shifted = x >> 2;
	// 	Now at least four 1s if k >= 3. There will be all one in all
	// bit i(i <= k) of variable x if k < 3.
	x = x | shifted;

	shifted = x >> 4;
	x = x | shifted;

	shifted = x >> 8;
	x = x | shifted;

	shifted = x >> 16;
	x = x | shifted;

	return x & ~(x >> 1);
}



int main()
{
	unsigned int x = 0;
	unsigned int y = 5;
	unsigned int z = -1;

	printf("leftmost_one(%d) -> 0x%x\n", x, leftmost_one(x));
	printf("leftmost_one(%d) -> 0x%x\n", y, leftmost_one(y));
	printf("leftmost_one(%d) -> 0x%x\n", z, leftmost_one(z));

	return 0;
}
