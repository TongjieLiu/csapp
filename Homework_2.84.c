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




unsigned int f2u(float f)
{
	unsigned int *p = (unsigned int *)&f;

	return *p;
}



int float_le(float x, float y)
{
	unsigned int ux = f2u(x);
	unsigned int uy = f2u(y);

	unsigned int sx = ux >> 31;
	unsigned int sy = uy >> 31;

	return ((ux & 0x7fffffff) == 0 && (uy & 0x7fffffff) == 0)	|| \
	       sx > sy							|| \
               (sx == sy && (sx == 1 ? ux >= uy : ux <= uy));
}




void print_q_and_a(float a, float b)
{
	printf("%f <= %f?    %d\n", \
	       (double)a, (double)b, float_le(a, b));
}



int main()
{
	print_q_and_a(0.0f, -0.0f);
	print_q_and_a(-0.0f, 0.0f);
	print_q_and_a(0.0f, 0.0f);
	print_q_and_a(-0.0f, -0.0f);

	puts("");

	print_q_and_a(0.0f, 123.0f);
	print_q_and_a(-0.0f, 123.0f);
	print_q_and_a(0.0f, -4567.0f);
	print_q_and_a(-0.0f, -4567.0f);

	puts("");

	print_q_and_a(100.0f, 0.0f);
	print_q_and_a(-100.0f, 0.0f);
	print_q_and_a(100.0f, -0.0f);
	print_q_and_a(-100.0f, -0.0f);

	puts("");

	print_q_and_a(12345.0f, 2468.0f);
	print_q_and_a(12345.0f, -2468.0f);
	print_q_and_a(-12345.0f, 2468.0f);
	print_q_and_a(-12345.0f, -2468.0f);
}
