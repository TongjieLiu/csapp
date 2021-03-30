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




typedef unsigned int float_bits;




float_bits float_i2f(int i)
{
	unsigned int sign, exp, frac;


	int j;
	int n_leftmost_zeros;

	int E, n_extra_bits;
	unsigned int mask;
	float_bits fb, fb_floor, fb_middle;



	// 	All values that can be stored in a int type variable except
	// 0 are normalized.
	if (i == 0) {					// int -> + 0.0
		sign = exp = frac = 0;
	} else {					// int -> normalized values
		if (i >= 0) {
			sign = 0;
			fb = i;
		} else {
			sign = 1;
			fb = -i;
		}


		n_leftmost_zeros = 0;
		for (j = 31; j >= 0; j--) {
			if (((fb >> j) & 1) == 0)
				n_leftmost_zeros++;
			else
				break;
		}


		E = 32 - n_leftmost_zeros - 1;
		exp = E + 127;

		// drop off the leftmost 1, since M = f + 1
		mask = (1 << E) - 1;
		fb = fb & mask;

		// compute frac: rounding-to-even mode
		if (E <= 23) {
			frac = fb << (23 - E);
		} else { // E > 23
			n_extra_bits = E - 23;

			fb_floor = (fb >> n_extra_bits) << n_extra_bits;
			fb_middle = fb_floor + (1 << (n_extra_bits - 1));

			mask = 1 << n_extra_bits;
			if (fb > fb_middle) {
				frac = (fb >> n_extra_bits) + 1;
			} else if (fb < fb_middle) {
				frac = fb >> n_extra_bits;
			} else { // fb = fb_middle
				if ((fb_floor & mask) == 0)	// even
					frac = fb >> n_extra_bits;
				else				// odd
					frac = (fb >> n_extra_bits) + 1;
			}

			// 	The rounding operation cause this. Frac = 0x7fffff
			// before it has happened, but now frac = 0x800000 and M =
			// 1 + frac = 2.
			if (frac >= 0x800000) {
				frac = 0;
				exp++;
			}
		}
	}



	return (sign << 31) | (exp << 23) | frac;
}




float u2f(unsigned int u)
{
	float *p = (float *)&u;

	return *p;
}



unsigned int f2u(float f)
{
	unsigned int *p = (unsigned int *)&f;

	return *p;
}



int main()
{
	long i;

	float f, fb;

	long diff = 0;



	for (i = INT_MIN; i <= INT_MAX; i++) {
		f = (float)(int)i;
		fb = u2f(float_i2f((int)i));
		
		if (f != fb) {
			diff++;

			// There will be no NaN, so just print all differences
			printf("i = %d, f = %f(0x%X), float_i2f -> %f(0x%X)\n", \
			       (int)i, (double)f, f2u(f), (double)fb, f2u(fb));
		}
	}


	puts("Test result:");
	if (diff)
		printf("\tDifferent: %ld operations\n", diff);
	else
		puts("\tNo difference");



	return 0;
}
