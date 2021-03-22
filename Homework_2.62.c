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



int int_shifts_are_arithmetic()
{
	int ivar = 1;
	int shift_bit_num = (sizeof(int) << 3) - 1;

	// after this, the most significant bit will be 1 and the rest 0
	ivar = ivar << shift_bit_num;

	// 	After this, ivar will be all 1 in its bit representaion
	// if right shifts of type int are arithmetic.
	ivar = ivar >> shift_bit_num;

	return !~ivar;
}



int main()
{
	printf("int shifts are arithmetic? %d\n", int_shifts_are_arithmetic());

	return 0;
}
