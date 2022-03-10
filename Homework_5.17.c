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




void *new_memset(void *s, int c, size_t n)
{
	size_t i;
	size_t limit;
	char *char_ptr;
	size_t address;	//	pointer arithmetic is not appropriate for
			// memory alignment checking
	unsigned long word, *word_ptr, byte;


	byte = c; // "int" is too small to left shift more than 32 bits

	word = byte;
	word = word | (byte << 8); 
	word = word | (byte << 16); 
	word = word | (byte << 24); 
	word = word | (byte << 32); 
	word = word | (byte << 40); 
	word = word | (byte << 48); 
	word = word | (byte << 56); 


	i = 0;
	address = (size_t)s;
	char_ptr = (char *)s;
	limit = 8 - address % 8;
	for (; i < limit; char_ptr++, i++) {
		if (i >= n)
			return s;
		else
			*char_ptr = (char)c;
	}


	word_ptr = (unsigned long *)char_ptr;
	if (n >= 7) {	//	i < limit is a unsigned comparison, and n - 7
			// could be a very large and positive number when it
			// underflows.
		limit = n - 7;
		for (; i < limit; i += 8, word_ptr++)
			*word_ptr = word;
	}


	char_ptr = (char *)word_ptr;
	for (; i < n; i++, char_ptr++)
		*char_ptr = (char)c;


	return s;
}




// #define BUFSIZE 5
// #define BUFSIZE 40
#define BUFSIZE 83


int main()
{
	int i;
	char buf[BUFSIZE];


	for (i = 0; i < BUFSIZE; i++)
		buf[i] = 'a';


	puts("old:");


	for (i = 0; i < BUFSIZE; i++) {
		fputc((int)buf[i], stdout);

		if(i % 8 == 7)
			puts("");
	}


	puts("\n\nnew:");


	new_memset(buf, 'b', BUFSIZE);


	for (i = 0; i < BUFSIZE; i++) {
		fputc((int)buf[i], stdout);

		if(i % 8 == 7)
			puts("");
	}

	puts("");


	return 0;
}
