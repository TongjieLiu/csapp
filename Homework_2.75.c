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

/* 	According to Equation 2.18, we have:
  	x' * y' = (x + x_{w - 1} * 2^w) * (y + y_{w - 1} * 2^w)
	        = x * y +						term 1
		  x_{w - 1} * y * 2^w +					term 2
		  y_{w - 1} * x * 2^w +					term 3
		  x_{w - 1} * y_{w - 1} * 2^w * 2^w			term 4
   Here, both x' and y' are unsigned numbers, both x and y are two's complement
   numbers. By calling function signed_high_prod, we can compute unsigned_high_
   prod as:
   	unsigned_high_prod = signed_high_prod +				term 1
		             x_{w - 1} * y +				term 2
		             y_{w - 1} * x +				term 3
		             x_{w - 1} * y_{w - 1} * 2^w		term 4
   	But unfortunately, term 4 has 2^w > 2^{w - 1} -1 = the maximum value of
   two's complement number. In another word, term 4 can not be represented by a
   variable of type int when x_{w - 1} * y_{w - 1} equals 1.
   	Since we have the fact that:
	2^w = 2 * 2^{w - 1}
	    = 2 * 2^{w - 1} -2 + 2
	    = (2^{w - 1} - 1) + (2^{w - 1} - 1) + 2
   We can solve it by substitution of 2^w:
   	unsigned_high_prod = signed_high_prod +				term 1
		             x_{w - 1} * y +				term 2
		             y_{w - 1} * x +				term 3
		             x_{w - 1} * y_{w - 1} * (2^{w - 1} - 1) +	term 4
		             x_{w - 1} * y_{w - 1} * (2^{w - 1} - 1) +	term 5
		             x_{w - 1} * y_{w - 1} * 2			term 6 */
unsigned int unsigned_high_prod(unsigned int x, unsigned int y)
{
	int uint_bit_size = sizeof(unsigned int) << 3;
	int shift_amount = uint_bit_size - 1;

	int sign_bit_x = x >> shift_amount;
	int sign_bit_y = y >> shift_amount;
	int int_max_val = (1 << shift_amount) - 1;

	/* int result = signed_high_prod((int)x, (int)y)	+ \
		        sign_bit_x * (int)y			+ \
		        sign_bit_y * (int)x			+ \
		        sign_bit_x * sign_bit_y * int_max_val	+ \
		        sign_bit_x * sign_bit_y * int_max_val	+ \
		        sign_bit_x * sign_bit_y * 2;
	    	We can see that sign_bit_x and sign_bit_y can only be either 0 or 1,
	   and it also make sign_bit_x * sign_bit_y being either 0 or 1.
           	Since 0 * x = 0 = 0...0 & x and 1 * x = x = 1...1 & x, we can solve
	   this by the following version: */
	int sign_part_x = (int)x >> shift_amount;
	int sign_part_y = (int)y >> shift_amount;

	int sign_prod = sign_part_x & sign_bit_y;
	int shifted_sign_prod = (sign_prod << shift_amount) >> shift_amount;
	int term45 = shifted_sign_prod & int_max_val;

	int result = signed_high_prod((int)x, (int)y)		+ \
		     sign_part_x & (int)y			+ \
		     sign_part_y & (int)x			+ \
		     term45					+ \
		     term45					+ \
		     sign_prod << 1;

	return (unsigned int)result;
}
