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



int odd_ones(unsigned int x)
{
	unsigned int left_end;


	//	We can think of an odd number as the sum of a 1 and some 2s, and
	// how many 2s are here is not that important in the process of determin-
	// ing whether this number is odd or even.
	// 	By the help of operator exclusive-or, the high-order 16 bits and
	// the low-order 16 bits will cancel out each other in each bit of the
	// result if two input bits which have the same relative position both
	// have 1 as their value, and leave relative positions which only have a
	// single 1 keeping their 1s.
	//	The right end of the word need not be masked, since we only need
	// the least significant bit to compute the result.
	left_end = x >> 16;
	x = left_end ^ x;

	// repeat the computation above again
	left_end = x >> 8;
	x = left_end ^ x;

	left_end = x >> 4;
	x = left_end ^ x;

	left_end = x >> 2;
	x = left_end ^ x;

	left_end = x >> 1;
	x = left_end ^ x;

	return (x & 0x1) == 1;
}



int main()
{
	unsigned int x = 0;
	unsigned int y = 5;
	unsigned int z = 0x1FF;

	printf("odd_ones(%d)? %d\n", x, odd_ones(x));
	printf("odd_ones(%d)? %d\n", y, odd_ones(y));
	printf("odd_ones(%d)? %d\n", z, odd_ones(z));

	return 0;
}
