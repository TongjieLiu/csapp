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




float u2f(unsigned int u)
{
	float *p = (float *)&u;

	return *p;
}



float fpwr2(int x)
{
	unsigned int exp, frac;
	unsigned int u;


	if (x < -149) {		// Too small, return 0.0
				// n = 23 => x < -126 - 23 = -149
		exp = 0;
		frac = 0;
	}else if (x < -126){	// Denormalized result
				// 1 - (2^{8 - 1} - 1) = -126
		exp = 0;
		frac = 0x800000 >> (-126 - x); // n = 23 = 4 * 5 + 3
	} else if (x < 128){	// Normalized result
				//   [(2^8 - 1 - 1) - (2^{8 - 1} - 1)] + 1
				// = 2^7 = 128
		exp = x + 127; // e = E + bias = x + 127
		frac = 0; // f = 1.000... in binary representation
	} else {		// Too big, return positive infinity
		exp = 0xFF; // k = 8
		frac = 0;
	}


	u = exp << 23 | frac;

	return u2f(u);
}




void print_comparison(int x)
{
	printf("2^%d =\t%.60f,\n" "fpwr2(%d) =\t%.60f\n\n", \
		x, exp2f(x), x, (double)fpwr2(x));
}



int main()
{
	print_comparison(0);
	print_comparison(1);
	print_comparison(2);
	
	puts("\n\n\n");

	print_comparison(-1);
	print_comparison(-2);

	puts("\n\n\n");

	print_comparison(-148);
	print_comparison(-149);
	print_comparison(-150);

	puts("\n\n\n");

	print_comparison(-125);
	print_comparison(-126);
	print_comparison(-127);

	puts("\n\n\n");

	print_comparison(126);
	print_comparison(127);
	print_comparison(128);

	return 0;
}
