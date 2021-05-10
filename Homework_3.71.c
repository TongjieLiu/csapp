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



#define GOOD_ECHO_BUF_SIZE 8



int good_echo()
{
	int eol;
	char *p, *end;

	char *s;
	char buf[GOOD_ECHO_BUF_SIZE];

	end = &buf[GOOD_ECHO_BUF_SIZE - 1];
	do{
		s = fgets(buf, GOOD_ECHO_BUF_SIZE, stdin);
		if (s == NULL)
			return -1;
		else
			fputs(s, stdout);

		for (eol = 0, p = s; p <= end; p++){
			if (*p == '\n') {
				eol = 1;
				break;
			}
		}
	} while(!eol);

	return 0;
}



int main()
{
	good_echo();

	return 0;
}
