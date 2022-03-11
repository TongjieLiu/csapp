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




/*	If we try to do a 2 x 1 loop unrolling on the Horner's method
 * version, each iteration computes:
 * 	result	= a[i - 1] + x * (a[i] + x * result)
 *		= a[i - 1] + x * a[i] + x^2 * result
 *		= (a[i - 1] + x * a[i]) + x^2 * result
 *
 *	Note that we applied the reassociation transformation in the last
 * step. As a result, there are only 2 operations in the critical path of
 * the register representing variable result, which is a floating-point
 * addition and a floating-point multiplication.
 *
 *	Of course, this is not good enough, since the version in Practice
 * Problem 5.5 has only 2 floating-point additions for 2 iterations, which
 * is faster than our method. Note that 1 iteration in our method is 2
 * iterations in Practice Problem 5.5 in terms of polynomial terms we try
 * to compute.
 *
 * 	But we could further unrolling the loop, and this is very effective.
 * For example, a 3 x 1a loop unrolling compute the following expression in
 * each iteration:
 * 	result	= a[i - 2] + x * (a[i - 1] + x * a[i] + x^2 * result)
 * 		= a[i - 2] + x * a[i - 1] + x^2 * a[i] + x^3 * result
 * 		= (a[i - 2] + x * a[i - 1] + x^2 * a[i]) + x^3 * result
 *	Since there are only a floating-point addition and a floating-point
 * multiplication in the critical path of the register representing result,
 * we could say this method is faster than all two solutions in the book. In
 * details, Practice Problem 5.5 needs at least 3 * 3 = 9 cycles for 3
 * polynomial terms, and Practice Problem 5.6 needs at least (3 + 5) * 3 = 24
 * cycles, but our method needs only 3 + 5 = 8 cycles as its ideal speed. */
double poly(double a[], double x, long degree)
{
	long i;
	double result, x_squared, x_cubed;


	result = a[degree];
	x_squared = x * x;
	x_cubed = x_squared * x;


	/* i - 2 >= 0   =>   i >= 2 */
	for (i = degree - 1; i >= 2; i -= 3)
		result = (a[i - 2] + x * a[i - 1] + x_squared * a[i]) + \
			 x_cubed * result;


	for (; i >= 0; i--)
		result = a[i] + x * result;


	return result;
}




int main()
{
	double result;
	double a[] = {1.0, 2.0, 3.0, 4.0, 5.0};

	result = poly(a, 10.0, 4);
	printf("result = %f\n", result);

	return 0;
}
