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

long switch_prob(long x, long n)
{
	long result = x;

	switch (n)
	{
		case 0x3c:
		case 0x3e:	result = 8 * x;
				break;

		case 0x3d:	result = x >> 3;
				break;

		case 0x3e:	result = 15 * x;
				x = result;

		case 0x3f:	result = x * x + 0x4b;
				break;

		default:	result = x + 0x4b;
	}

	return result;
}
