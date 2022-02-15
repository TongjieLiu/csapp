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




void bubble(long *data, long count)
{
	long *pos, *p;
	long tmp;


	for (pos = data + (count - 1); pos > data; pos--) {
		for (p = data; p < pos; p++) {
			if (*p > *(p + 1)) {
				tmp = *(p + 1);
				*(p + 1) = *p;
				*p = tmp;
			}
		}
	}
}




void print_array(char *prefix, long *array, long len)
{
	int i;


	fputs(prefix, stdout);

	for (i = 0; i < len; i++)
		printf("%ld ", array[i]);

	puts("");
}


int main()
{
	long a[3] = {2, 1, 3};
	long b[4] = {10, 15, 20, 25};
	long c[9] = {-8, 8, -6, 6, -4, 4, -2, 2, 0};
	long d[1] = {2022};


	print_array("a: ", a, 3);
	print_array("b: ", b, 4);
	print_array("c: ", c, 9);
	print_array("d: ", d, 1);


	bubble(a, 3);
	bubble(b, 4);
	bubble(c, 9);
	bubble(d, 1);


	puts("After bubble-sorting ...");

	print_array("a: ", a, 3);
	print_array("b: ", b, 4);
	print_array("c: ", c, 9);
	print_array("d: ", d, 1);


	return 0;
}
