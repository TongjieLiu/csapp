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




float_bits float_half(float_bits f)
{
	unsigned int sign = f >> 31;
	unsigned int exp = f >> 23 & 0xFF;
	unsigned int frac = f & 0x7FFFFF;

	unsigned half_frac, floor_frac, middle_frac;


	if (exp == 0) {				// denormalized values
		// rounding-toward-even mode
		half_frac = (frac << 2) >> 1; // compute 2 extra bits
		floor_frac = (frac >> 1) << 2;
		middle_frac = floor_frac + 2;

		if (half_frac > middle_frac) {
			frac = (floor_frac + 4) >> 2;
		}else if (half_frac < middle_frac) {
			frac = floor_frac >> 2;
		} else { // half_frac = middle_frac
			if ((floor_frac & 0x7) == 0)
				frac = floor_frac >> 2;
			else
				frac = (floor_frac + 4) >> 2;
		}
	} else if (exp == 1) {			// normalized values
		exp = 0; // e = 0 and e = 1 have the same E


		// rounding-toward-even mode
		frac = frac + 0x800000;	// M = f + 1, when exp = 1;
					// M = f, when exp = 0

		half_frac = (frac << 2) >> 1; // compute 2 extra bits
		floor_frac = (frac >> 1) << 2;
		middle_frac = floor_frac + 2;

		if (half_frac > middle_frac) {
			frac = (floor_frac + 4) >> 2;
		}else if (half_frac < middle_frac) {
			frac = floor_frac >> 2;
		} else { // half_frac = middle_frac
			if ((floor_frac & 0x7) == 0)
				frac = floor_frac >> 2;
			else
				frac = (floor_frac + 4) >> 2;
		}
	} else if (exp < 255)
		exp--;

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
	long max = UINT_MAX;

	float half, half_fb;

	long diff = 0;



	for (i = 0; i <= max; i++) {
		half = 0.5 * u2f((unsigned int)i);
		half_fb = u2f(float_half((float_bits)i));
		
		if (f2u(half) != f2u(half_fb)) {
			diff++;
			if (half == half) // x is not equal to x itself when x is a NaN
				printf("%f(0x%X): "					\
					"0.5 * f = %f(0x%X), "				\
					"float_half -> %f(0x%X)\n",			\
					(double)u2f((unsigned int)i), (unsigned int)i,	\
					(double)half, f2u(half),			\
					(double)half_fb, f2u(half_fb));
		}
	}


	puts("Test result:");
	if (diff)
		printf("\tDifferent: %ld operations"	\
			"(2^23 = 8388608)\n",		\
			diff);
	else
		puts("\tNo difference");



	return 0;
}
