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

#include <limits.h>
#include <stdio.h>



int saturating_add(int x, int y)
{
	int int_bit_size = sizeof(int) << 3;
	int shift_amount = int_bit_size - 1;

	int x_negative = x >> shift_amount;
	int y_negative = y >> shift_amount; 

	int sum = x + y;
	int sum_negative = sum >> shift_amount;

	/* x >= 0, y >= 0, x +^t y <  0    =>    positive overflow
	   x <  0, y <  0, x +^t y >= 0    =>    negative overflow */
	int positive_overflow = !x_negative	&& \
				!y_negative	&& \
				sum_negative;
	int negative_overflow = x_negative	&& \
				y_negative	&& \
				!sum_negative;


	int P = (positive_overflow << shift_amount) >> shift_amount;
	int N = (negative_overflow << shift_amount) >> shift_amount;
	/* Our goal:
	   	positive + positive -> sum,	normal
		                       TMax,	positive overflow

	   	negative + positive -> sum

	   	negative + negative -> sum,	normal
		                       TMin,	negative overflow

	   => saturating_add = (!p && !n) * sum + p * TMax + n * Tmin
	   Here, p = 1 if positive overflow, p = 0 otherwise,
	         n = 1 if negative overflow, n = 0 otherwise.


	   0 * x = 0 = x & 0...0
	   1 * x = x = x & 1...1
	   
	   => saturating_add = ((~P & ~N) & sum) + (P & TMax) + (N & Tmin)
	   Here, P = 1...1 if positive overflow, P = 0...0 otherwise,
	         N = 1...1 if negative overflow, N = 0...0 otherwise. */
	int tmin = 1 << shift_amount;
	int tmax = tmin - 1;

	return ((~P & ~N) & sum)	+ \
	       (P & tmax)		+ \
	       (N & tmin);
}



void print_comparison(int x, int y)
{
	printf("%d + %d = %d, saturating_add(%d, %d) = %d\n\n", \
		x, y, x + y, x, y, saturating_add(x, y));
}



int main()
{
	print_comparison(1, 1);
	print_comparison(987654321, 123456789);
	print_comparison(-324, 2021);
	print_comparison(12345, -6789);
	print_comparison(-1000, -10000);

	print_comparison(INT_MAX, INT_MAX);
	print_comparison(INT_MAX, INT_MIN);
	print_comparison(INT_MIN, INT_MIN);

	return 0;
}
