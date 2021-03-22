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



unsigned int srl(unsigned int x, int k)
{
	unsigned int xsra = (int)x >> k; // perform shift arithmetically

	int rest_bit_num = (sizeof(unsigned int) << 3) - k;
	int mask = (1 << rest_bit_num) - 1;

	return xsra & mask;
}



int sra(int x, int k)
{
	int xsrl = (unsigned int)x >> k; // perform shift logically

	int int_bit_size = sizeof(int) << 3;
	int rest_bit_num = int_bit_size - k;

	// mask_xsrl in binary representation: 000...000111...111
	int mask_xsrl = (1 << (rest_bit_num - 1)) - 1;
	// msb_xsrl in binary representation: 000...001000...000 or 0...0
	int msb_xsrl = xsrl & ~mask_xsrl;

	// mask_x in binary representation: 1000...000
	int mask_x = 1 << (int_bit_size - 1);
	// msb_x in binary representation: 1000...000 or 0...0
	int msb_x = x & mask_x;

	return (msb_x - msb_xsrl) | msb_x | xsrl;
}



int main()
{
	int x = -1;
	int y = 12345;
	unsigned int ux = x;
	unsigned int uy = y;

	printf("sra(0x%x, 8) -> 0x%x\n", x, sra(x, 8));
	printf("sra(0x%x, 8) -> 0x%x\n", y, sra(y, 8));
	printf("srl(0x%x, 8) -> 0x%x\n", ux, srl(ux, 8));
	printf("srl(0x%x, 8) -> 0x%x\n", uy, srl(uy, 8));

	return 0;
}
