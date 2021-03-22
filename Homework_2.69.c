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



unsigned int rotate_left(unsigned int x, int n)
{
	int uint_bit_size = sizeof(unsigned int) << 3;
	int n_rest_bits = uint_bit_size - n;

	unsigned int mask = ((1 << n) - 1) << n_rest_bits; // mask = 1111000...000
	unsigned int drop_bits = x & mask;


	x = x << n;
	drop_bits = drop_bits >> n_rest_bits;

	return x | drop_bits;
}



int main()
{
	int x = 0x12345678;

	printf("rotate_left(0x%X, 0) -> 0x%X\n", x, rotate_left(x, 0));
	printf("rotate_left(0x%X, 4) -> 0x%X\n", x, rotate_left(x, 4));
	printf("rotate_left(0x%X, 20) -> 0x%X\n", x, rotate_left(x, 20));
	printf("rotate_left(0x%X, 31) -> 0x%X\n", x, rotate_left(x, 31));

	return 0;
}
