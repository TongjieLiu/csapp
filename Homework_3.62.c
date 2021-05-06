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

typedef enum {MODE_A, MODE_B, MODE_C, MODE_D, MODE_E} mode_t;



long switch3(long *p1, long *p2, mode_t action)
{
	long result = 0;

	switch (action)
	{
		case MODE_A:	result = *p2;
				*p2 = *p1;
				break;

		case MODE_B:	result = *p1 + *p2;
				*p1 = result;
				break;

		case MODE_C:	*p1 = 59;
				result = *p2;
				break;

		case MODE_D:	*p1 = *p2;

		case MODE_E:	result = 27;
				break;

		default:	result = 12;
	}

	return result;
}
