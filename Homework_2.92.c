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




float_bits float_negate(float_bits f)
{
	unsigned int sign = f >> 31;
	unsigned int exp = f >> 23 & 0xFF;
	unsigned int frac = f & 0x7FFFFF;

	if (!(exp == 0xFF && frac != 0))
		sign = ~sign;

	return (sign << 31) | (exp << 23) | frac;
}




float u2f(unsigned int u)
{
	float *p = (float *)&u;

	return *p;
}



int main()
{
	long i;
	long max = UINT_MAX;

	float nf, nfb;
	long error = 0;



	for (i = 0; i <= max; i++) {
		nf = - u2f((unsigned int)i);
		nfb = u2f(float_negate((float_bits)i));
		
		if (nf != nfb) {
			error++;
			if (error <= 100)
				printf("ERROR %ld: "			\
					"nf = %f, nfb = %f, "		\
					"f = %f\n",			\
					error,				\
					(double)nf, (double)nfb,	\
					(double)u2f((unsigned int)i));
			else if (error == 101)
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
