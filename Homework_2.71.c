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



typedef unsigned packed_t;



int xbyte(packed_t word, int bytenum)
{
	int shift_amount = 32 - 8;

	int signed_byte = word >> (bytenum << 3);

	return (signed_byte << shift_amount) >> shift_amount;
}



int main()
{
	// A. not performing sign extension after the extraction.
	
	packed_t x = 0x01ff0011;

	printf("xbyte(0x%X, 0) -> %d\n", x, xbyte(x, 0));
	printf("xbyte(0x%X, 1) -> %d\n", x, xbyte(x, 1));
	printf("xbyte(0x%X, 2) -> %d\n", x, xbyte(x, 2));
	printf("xbyte(0x%X, 3) -> %d\n", x, xbyte(x, 3));

	return 0;
}
