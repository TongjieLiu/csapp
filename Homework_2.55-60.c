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




void show_bytes(void *address, size_t size)
{
	size_t i;
	unsigned char *p = address;

	for (i = 0; i < size; i++){
		printf(" %.2x", p[i]);
	}
}



void show_int(int var)
{
	show_bytes(&var, sizeof(int));
}


void show_uint(unsigned int var)
{
	show_bytes(&var, sizeof(unsigned int));
}



void show_short(short var)
{
	show_bytes(&var, sizeof(short));
}



void show_long(long var)
{
	show_bytes(&var, sizeof(long));
}



void show_double(double var)
{
	show_bytes(&var, sizeof(double));
}




int is_little_endian()
{
	int ivar = 1;
	char *p = (char *)&ivar;

	if (*p == 1)
		return 1;
	else
		return 0;
}




unsigned int replace_byte(unsigned int x, int i, unsigned char b)
{
	int bits = 8 * i;
	unsigned int mask = 0xFF << bits;

	return (x & ~mask) | ((unsigned int)b << bits);
}




int main()
{
	int a = -1;
	unsigned int b = 12345;
	unsigned int B = b << 1;


	short s = 12345;
	long l = 12345;
	double d = 12345;


	unsigned int x = 0x89ABCDEF;
	unsigned int y = 0x76543210;




	printf("%d(int):", a);
	show_int(a);
	printf("\n%d -> Hex: %x\n", a, a);


	printf("\n%u(unsigned int):", b);
	show_uint(b);
	printf("\n%u -> Hex: %x\n", b, b);

	printf("\n%u(unsigned int):", B);
	show_uint(B);
	printf("\n%u -> Hex: %x\n", B, B);


	printf("\n%hd(short):", s);
	show_short(s);
	printf("\n%hd -> Hex: %hx\n", s, s);


	printf("\n%ld(long):", l);
	show_long(l);
	printf("\n%ld -> Hex: %lx\n", l, l);


	printf("\n%f(double):", d);
	show_double(d);
	puts("\n");




	// Homework problem 2.58
	printf("IS LITTLE ENDIAN(1 = YES, 0 = NO)? %d", is_little_endian());
	puts("\n");




	// Homework problem 2.59
	printf("x = 0x%X\ny = 0x%X\n", x, y);
	printf("RESULT OF HOMEWORK PROBLEM 2.59 = 0x%X\n\n", \
		(x & 0xFF) | (y & ~0xFF));




	// Homework problem 2.60
	printf("REPLACE_BYTE(0x12345678, 2, 0xAB) -> 0x%X\n", \
		replace_byte(0x12345678, 2, 0xAB));
	printf("REPLACE_BYTE(0x12345678, 0, 0xAB) -> 0x%X\n", \
		replace_byte(0x12345678, 0, 0xAB));




	return 0;
}
