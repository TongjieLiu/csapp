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



int int_size_is_32b()
{
	int set_msb = 1 << 31;

	int beyond_msb = set_msb;
	beyond_msb = beyond_msb << 1;

	return set_msb && !beyond_msb;
}



int int_size_is_32c()
{
	int set_msb = 1 << 1;
	int beyond_msb = 1 << 2;

	set_msb = set_msb << 15;
	set_msb = set_msb << 15;
	beyond_msb = beyond_msb << 15;
	beyond_msb = beyond_msb << 15;

	return set_msb && !beyond_msb;
}



int main()
{
	// 	A. In the second statement, the actual left shift amount = 32 mod
	// width of int = 0.

	printf("B: %d\n", int_size_is_32b());
	printf("C: %d\n", int_size_is_32c());

	return 0;
}
