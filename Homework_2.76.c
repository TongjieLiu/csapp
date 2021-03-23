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

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



void *calloc(size_t nmemb, size_t size)
{
	char *address;

	size_t prod = nmemb * size;
	int mul_ok = !nmemb || (prod / nmemb) == size;


	puts("You are using the version of function calloc " \
	     "from homework problem 2.76");

	if (!mul_ok)
		return NULL;

	address = malloc(prod);
	if (address == NULL)
		return NULL;

	return memset(address, (int)0, prod);
}



int main()
{
	size_t n, size;
	char *address_1, *address_2;


	n = (size_t)exp2(30) + 1;
	size = exp2(34);
	address_1 = calloc(n, size);

	printf("ADDRESS 1 = 0x%p\n", address_1);


 	n = (size_t)exp2(20) + 1;
	size = exp2(12);
	address_2 = calloc(n, size);

	printf("ADDRESS 2 = 0x%p\n", address_2);


	return 0;
}
