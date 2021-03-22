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



int fits_bits(int x, int n)
{
	/* 	We can solve it by first truncated x into only lower-order n bits
	   in a w-bits word of type int called t, and t has a corresponding n-bits
	   word called a.
	   	Let the sign bit of a be s, and its bit representaion be [s, x_{n -
	   2}, x_{n - 3}, ... , x_0]. It can be expanded to a w-bits words of int
	   type and can be represented as bit vector b = [s, s, ... , s, x_{n - 2},
	   x_{n - 3}, ... , x_0].
	   	Here, t and b have the same numeric value. B will not be equal to
	   x, if x can not be fitted into n bits. */
	int w = sizeof(int) << 3;
	int n_rest_bits = w - n;

	int t, b;
	int mask, sign_bit, sign_part;


	// truncating x into t
	mask = 1 << (n - 1);
	mask = mask | (mask - 1);
	// mask now has all 1 in lower-order n bits, and the rest bits are 0s
	t = x & mask;

	// constructing b
	mask = 1 << (n - 1);
	sign_bit = t & mask;
	// arithmetic right shift for signed int type variable
	sign_part = (sign_bit << n_rest_bits) >> n_rest_bits;
	b = t | sign_part;

	return b == x;
}



int main()
{
	int a = 100;
	int b = -16;
	// the maximum value of 16-bits word in two's complement representaion = 32,767
	int c = 33000;
	int d = 32767;
	// the minimum value of 16-bits word in two's complement representaion = -32,768
	int e = -999999;
	int f = -32768;

	printf("fits_bits(%d, 16)? %d\n", a, fits_bits(a, 16));
	printf("fits_bits(%d, 16)? %d\n", b, fits_bits(b, 16));
	printf("fits_bits(%d, 16)? %d\n", c, fits_bits(c, 16));
	printf("fits_bits(%d, 16)? %d\n", d, fits_bits(d, 16));
	printf("fits_bits(%d, 16)? %d\n", e, fits_bits(e, 16));
	printf("fits_bits(%d, 16)? %d\n", f, fits_bits(f, 16));

	return 0;
}
