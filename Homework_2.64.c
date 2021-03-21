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



int any_odd_one(unsigned int x)
{
	unsigned int mask = 0xAAAAAAAA;

	return !!(x & mask);
}



int main()
{
	unsigned int x = 3;
	unsigned int y = 4;
	unsigned int z = 8;

	printf("any_odd_one(%d)? %d\n", x, any_odd_one(x));
	printf("any_odd_one(%d)? %d\n", y, any_odd_one(y));
	printf("any_odd_one(%d)? %d\n", z, any_odd_one(z));

	return 0;
}
