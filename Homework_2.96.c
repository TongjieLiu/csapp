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




int float_f2i(float_bits f)
{
	unsigned int sign = f >> 31;
	unsigned int exp = f >> 23 & 0xFF;
	unsigned int frac = f & 0x7FFFFF;

	int result;
	
	int E;
	int n_left_shift;



	if (exp <= 126) { // E = -1, e = -1 + 127 = 126
		result = 0;
	} else if (exp <= 157) { // 32 - 1 - 1 = 30 = E, e = 30 + 127 = 157
		frac = frac + 0x800000; // M = 1 + f for normalized values


		// rounding-toward-zero mode
		E = exp - 127;
		n_left_shift = E - 23; // n = 23

		if (sign == 0) { // f >= 0
			result = n_left_shift >= 0 ?	\
			         frac << n_left_shift :	\
			         frac >> -n_left_shift;
		} else {
			result = n_left_shift >= 0 ?	\
			         frac << n_left_shift :	\
			         frac >> -n_left_shift;

			result = - result;
		}
	} else {
		result = 0x80000000;
	}



	return result;
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
	float f;

	int int_f, int_fb;

	long diff = 0;



	for (i = 0; i <= max; i++) {
		f = u2f((unsigned int)i);

		int_f = (int)f;
		int_fb = float_f2i((float_bits)i);
		
		if (int_f != int_fb) {
			diff++;
			if (f == f) // x is not equal to x itself when x is a NaN
				printf("%f: "				\
					"(int)f = %d, "			\
					"float_f2i -> %d\n",		\
					(double)f,			\
					int_f,				\
					int_fb);
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
