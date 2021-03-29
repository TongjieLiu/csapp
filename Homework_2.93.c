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
#include <math.h>
#include <stdio.h>




typedef unsigned int float_bits;




float_bits float_absval(float_bits f)
{
	unsigned int sign = f >> 31;
	unsigned int exp = f >> 23 & 0xFF;
	unsigned int frac = f & 0x7FFFFF;

	if (!(exp == 0xFF && frac != 0))
		sign = 0;

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

	float abs, abs_fb;

	long error = 0;
	long error_print_max = 100;
	long error_print_end = error_print_max + 1;



	for (i = 0; i <= max; i++) {
		abs = fabsf(u2f((unsigned int)i));
		abs_fb = u2f(float_absval((float_bits)i));
		
		if (f2u(abs) != f2u(abs_fb)) {
			error++;
			if (error <= error_print_max)
				printf("ERROR %ld: "			\
					"abs = %f(0x%X), "		\
					"abs_fb = %f(0x%X), "		\
					"f = %f\n",			\
					error,				\
					(double)abs, f2u(abs),		\
					(double)abs_fb, f2u(abs_fb),	\
					(double)u2f((unsigned int)i));
			else if (error == error_print_end)
				puts("...");
		}
	}


	puts("Test result:");
	if (error)
		printf("\tIncorrect: %ld errors\n", error);
	else
		puts("\tNo Error");



	return 0;
}
