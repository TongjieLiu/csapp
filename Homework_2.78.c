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

#include <math.h>
#include <stdio.h>



int divide_power2(int x, int k)
{
	/* 	To round the result toward zero, it have to be rounded down if
	   x >= 0, rounded up if x < 0.
	   	To round it down, we use x >> k; To round it up, we transform
	   x into x' = x + 2^k - 1, then perform x' >> k.
	   	Therefore, divide_power2(x, k) = x' >> k, x' = x + t * (2^k -
	   1), t = 0 if x >= 0, t = 1 if x < 0. */
	int bias = (1 << k) - 1;

	/* 0 * n = 0 = 0...0 & n
	   1 * n = n = 1...1 & n
	   
	   => t * bias = 0...0 & bias, t = 0
	                 1...1 & bias, t = 1 */
	int int_bit_size = sizeof(int) << 3;
	int shift_amount = int_bit_size - 1;
	int final_t = x >> shift_amount;

	int final_x = x + (final_t & bias);

	return final_x >> k;
}



void print_comparison(int x, int k)
{
	printf("x = %d: x / 2^%d = %d, divide_power2(%d, %d) = %d\n", \
		x, k, x / (int)exp2(k), x, k, divide_power2(x, k));
}



int main()
{
	print_comparison(2021, 3);
	print_comparison(12345, 4);

	print_comparison(-6789, 5);
	print_comparison(-10000, 6);

	return 0;
}
