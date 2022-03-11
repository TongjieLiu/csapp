/* A homework problem solution for the CS:APP3e

   Copyright (C) 2022 Tongjie Liu <tongjieandliu@gmail.com>.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>. */

#include <stdio.h>




/* 4 x 1a loop unrolling */
void psum(float a[], float p[], long n)
{
	long i, limit;
	float val, last_val;
	float sum_i_iplus1, sum_iplus2_iplus3;


	p[0] = a[0];
	last_val = a[0];


	limit = n - 3;
	for (i = 1; i < limit; i += 4) {
		sum_i_iplus1 = a[i] + a[i + 1];
		sum_iplus2_iplus3 = a[i + 2] + a[i + 3];

		val = last_val + a[i];
		p[i] = val;

		val = last_val + sum_i_iplus1;
		p[i + 1] = val;

		val = last_val + (sum_i_iplus1 + a[i + 2]);
		p[i + 2] = val;

		last_val = last_val + (sum_i_iplus1 + sum_iplus2_iplus3);
		p[i + 3] = last_val;
	}


	for (; i < n; i++) {
		val = last_val + a[i];
		p[i] = val;
		last_val = val;
	}
}




int main()
{
	int i;
	float a[7] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0};
	float p[7];


	psum(a, p, 7);


	for (i = 0; i < 7; i++)
		printf("%f ", (double)p[i]);

	puts("");


	return 0;
}
