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



int lower_one_mask(int n)
{
	int mask = 1 << (n - 1);

	return mask | (mask - 1);
}



int main()
{
	int x = 1;
	int y = 6;
	int z = 32;

	printf("lower_one_mask(%d) -> 0x%X\n", x, lower_one_mask(x));
	printf("lower_one_mask(%d) -> 0x%X\n", y, lower_one_mask(y));
	printf("lower_one_mask(%d) -> 0x%X\n", z, lower_one_mask(z));

	return 0;
}
