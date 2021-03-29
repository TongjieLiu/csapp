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




float_bits float_twice(float_bits f)
{
	unsigned int sign = f >> 31;
	unsigned int exp = f >> 23 & 0xFF;
	unsigned int frac = f & 0x7FFFFF;

	if (exp == 0) {				// denormalized values
		frac = frac * 2; 
		if (frac >= 0x800000) {	// M = 1 + f when e = 1, M = f when e = 0
					// frac * 2 need only 23 + 1 = 24 bits
			frac = frac - 0x800000;
			exp = 1;
		}
	} else if (1 <= exp && exp < 254) {	// normalized values
		exp++;
	} else if (exp == 254) {		// exp = 254 + 1 = 255 -> infinity
		exp = 255;
		frac = 0;
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
	long max = UINT_MAX;

	float t, tfb;

	long diff = 0;



	for (i = 0; i <= max; i++) {
		t = 2.0 * u2f((unsigned int)i);
		tfb = u2f(float_twice((float_bits)i));
		
		if (f2u(t) != f2u(tfb)) {
			diff++;
			if (t == t) // x is not equal to x itself when x is a NaN
				printf("f = %f, 2 * f = %f, float_twice -> %f\n",	\
					(double)u2f((unsigned int)i),			\
					(double)t,					\
					(double)tfb);
		}
	}


	puts("Test result:");
	if (diff)
		printf("\tDifferent: %ld operations\n", diff);
	else
		puts("\tNo difference");



	return 0;
}
