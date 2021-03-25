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




typedef int w_bit_data_type;




w_bit_data_type generate_bit_pattern_a(int k)
{
	/* 	Both ISO C90 and C99 require that the compiler takes constants as signed int
	   if possible, and converts size first, then sign.
	   	Therefore, 0 will be taken as signed int type, and ~0 will be sign extended
	   if w_bit_data_type is bigger than signed int. */
	w_bit_data_type all_1 = ~0;

	return all_1 << k;
}



w_bit_data_type generate_bit_pattern_b(int k, int j)
{
	w_bit_data_type x = generate_bit_pattern_a(k);

	return ~x << j;
}




int main()
{
	printf("generate_bit_pattern_a(%d) -> 0x%X\n", \
		0, generate_bit_pattern_a(0));
	printf("generate_bit_pattern_a(%d) -> 0x%X\n", \
		4, generate_bit_pattern_a(4));
	printf("generate_bit_pattern_a(%d) -> 0x%X\n", \
		16, generate_bit_pattern_a(16));

	printf("generate_bit_pattern_b(%d, %d) -> 0x%X\n", \
		0, 0, generate_bit_pattern_b(0, 0));
	printf("generate_bit_pattern_b(%d, %d) -> 0x%X\n", \
		8, 4, generate_bit_pattern_b(8, 4));
	printf("generate_bit_pattern_b(%d, %d) -> 0x%X\n", \
		4, 16, generate_bit_pattern_b(4, 16));

	return 0;
}
