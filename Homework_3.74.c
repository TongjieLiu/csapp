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

#include <limits.h>
#include <stdio.h>



typedef enum {NEG, ZERO, POS, OTHER} range_t;



range_t find_range(float x)
{
	int result;

	range_t range_neg = NEG;
	range_t range_zero = ZERO;
	range_t range_pos = POS;
	range_t range_other = OTHER;


	asm ("vxorps		%%xmm1, %%xmm1, %%xmm1\n"
	     "vucomiss	%%xmm1, %[x]\n"
	     "cmovb	%[neg], %[result]\n"
	     "cmove	%[zero], %[result]\n"
	     "cmova	%[pos], %[result]\n"
	     //		If x is a NaN, it may also be recognized as other
	     //	"range". Therefore, we have to check the PF flag at the
	     //	last step to overwrite any mistaken result made by the
	     //	conditional move insturctions above.
	     "cmovp	%[other], %[result]\n" // is x a NaN?
	     : [result] "=r" (result)// output operands
	     : [neg] "m" (range_neg), // input operands
	       [zero] "m" (range_zero),
	       [pos] "m" (range_pos),
	       [other] "m" (range_other),
	       [x] "x" (x)
	     : "%xmm1"// overwrited
	    );


	return result;
}



void print_computed_result(float x)
{
	int result;

	result = find_range(x);
	switch(result)
	{
		case NEG: printf("%f -> negative\n", (double)x);
			  break;
		case ZERO: printf("%f -> zero\n", (double)x);
			   break;
		case POS: printf("%f -> positive\n", (double)x);
			  break;
		case OTHER: printf("%f -> NaN\n", (double)x);
			    break;
	}
}



int main()
{
	long i;
	float *f;

	long error_count;

	range_t real_result, computed_result;

	for (i = 0, error_count = 0; i <= UINT_MAX; i++) {
		f = (float *)&i;
		computed_result = find_range(*f);

		if (*f < 0)
			real_result = NEG;
		else if (*f == 0)
			real_result = ZERO;
		else if (*f > 0)
			real_result = POS;
		else
			real_result = OTHER;

		if (real_result != computed_result) {
			printf("Error %ld: ", error_count);
			print_computed_result(*f);
			error_count++;
		}
	}

	printf("Error_count = %ld\n", error_count);

	return 0;
}
