/* A solution to the data lab in CS:APP3e

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
   along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

/* 
 * CS:APP Data Lab 
 * 
 * Tongjie Liu
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
//1
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
	/*    x y
	 * ^: 0 0 -> 0
	 *    0 1 -> 1
	 *    1 0 -> 1
	 *    1 1 -> 0
	 *
	 *    ~x y   a
	 * &: 1 0 -> 0
	 *    1 1 -> 1
	 *    0 0 -> 0
	 *    0 1 -> 0 
	 *
	 *    x ~y   b
	 * &: 0 1 -> 0
	 *    0 0 -> 0
	 *    1 1 -> 1
	 *    1 0 -> 0
	 *
	 *    ~a ~b  c   ~c
	 * &: 1 1 -> 1   0
	 *    0 1 -> 0   1
	 *    1 0 -> 0   1
	 *    1 1 -> 1   0 */

	int a, b;
	int not_a, not_b;
	int c, not_c;


	a = ~x & y;
	b = x & ~y;

	not_a = ~a;
	not_b = ~b;

	c = not_a & not_b;
	not_c = ~c;


	return not_c;
}




/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
	return 1 << 31; // 1000...000
}




//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
	int a, b, c;
	int not_neg_one;


	/* Tmax + 1 -> Tmin       a
	 * Tmax + Tmin -> -1      b
	 * -1 + 1 -> 0            c
	 * !0 -> 1
	 *
	 *	But we also know that
	 * c = f(x) = 2x + 2
	 * => x = -1 when c = 0 */
	a = x + 1;
	b = x + a;
	c = b + 1;


	/*	If we try to evaluate x ^ -1, we'll meet 2 situations:
	 *	1. x = -1 -> 0;
	 *	2. x != -1 -> not 0
	 * But unfortunately, we can't use -1 in this exercise. And
	 * here is the alternative method: */
	not_neg_one = (x + 1) ^ 0;


	return !c & (!!not_neg_one); // return value should be 0 or 1
}




/* 
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
	int part;
	int oddbits_are_ones;

	int only_keep_oddbits;


	part = 0xAA; // binary: 1010 1010
	oddbits_are_ones = part | (part << 8) | (part << 16) | (part << 24);

	only_keep_oddbits = x & oddbits_are_ones;

	return !(only_keep_oddbits ^ oddbits_are_ones);
}




/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
	/*	We all know that the name of two's complement number comes
	 * from its representation of the negative integer:
	 * 	2^N - x = -x, where x can be any non-negative integer
	 * After moving -x to the left side and x to the right side, we'll
	 * have:
	 * 	2^N - (-x) = x, where x can be any non-negative integer
	 * We can name y as -x, and we'll have:
	 * 	2^N - y = -y, where y can be any negative integer
	 * After that, we can conclude that:
	 * 	2^N - x = -x, where x can be any integer, not just non-negative
	 * integer
	 *
	 *	By subtracting both sides by 1, we'll have:
	 * 	(2^N - 1) - x = -x - 1
	 * And (2^N - 1) in binary is 111...111, the entire subtraction of x
	 * from (2^N - 1) can be splitted into bit subtractions. In each bit,
	 * the subtraction needs no borrowing from the left of the bit. Thus,
	 * each bit of 111...111 minus the corresponding bit of x is 1 if
	 * that bit of x is 0, 0 if that bit is 1. In other words (2^N - 1)
	 * - x = (111...111)_2 - x = ~x.
	 * 	Then, the relation between x and -x can be written as below:
	 * 	~x = -x - 1, where x can be any integer
	 * After moving 1 from the right side to the left, we can conclude that:
	 * 	~x + 1 = -x, where x can be any integer. */
	return ~x + 1;
}




//3
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
	/* 0x30 in binary is 0011 0000;
	 * 0x39 in binary is 0011 1001
	 *
	 * 	Numbers satisfied the condition can be divided into 3 class:
	 * 	1. written as 0011 0xyz in binary
	 * 	2. written as 0011 1001 in binary(0x39 in hexadecimal)
	 * 	3. written as 0011 1000 in binary(0x38 in hexadecimal)
	 * And the first class can be divided into 2 parts:
	 * 	1. right-most 3 bits
	 * 	2. left-most 29 bits
	 * The second part if fixed, and the part can be anything. */
	int left_part;
	int is_first_class, is_second_class, is_third_class;


	left_part = x & ~0x07; // 0x07: 0000 0111
	is_first_class = !(left_part ^ 0x30); // 0x30: 0011 0000


	is_second_class = !(x ^ 0x39);


	is_third_class = !(x ^ 0x38);


	return is_first_class | is_second_class | is_third_class;
}




/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
	int condition;
	int mask;


	condition = !!(x ^ 0); // we only want 0 and 1 as condition


	/* 0 + 111...111 = 111...111;
	 * 1 + 111...111 = 0 */
	mask = condition + (~0);


	return (y & ~mask) | (z & mask); // 0 | x -> x
}




/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
	int sign_x, sign_y, sign;
	int is_class1, is_class2, is_class3;
	int sum;


	/* 000...000 or 111...111 */
	sign_x = (x >> 31) & 1;
	sign_y = (y >> 31) & 1;


	/* class 1: x <= y when x is negative and y is non-negative */
	is_class1 = sign_x & !sign_y;


	/* class 2: -x + y >= 0 when x and y are both non-negative */
	sum = (~x + 1) + y;
	sign = sum >> 31;
	is_class2 = !sign_x & !sign_y & !sign; // result of ! is alway 1 or 0


	/* class 3: (~x + 1) + y >= 0 when x and y are both negative
	 *
	 *	We have to pay attention to the fact that -^t Tmin = Tmin
	 * != -Tmin. Thus, (~Tmin + 1) is not -Tmin, but Tmin itself.
	 * Moreover, the result of (~x + 1) + y is not -x + y when x = Tmin,
	 * but x + y.
	 *
	 *	There are 2 situations when x = Tmin, namely:
	 *	1. x = Tmin and y != Tmin
	 *		First, we try to compute:
	 *			  (~x + 1) + y
	 *			= Tmin + y > 0
	 *		Since x = Tmin and y != Tmin, we have:
	 *			x < y
	 *	2. x = y = Tmin
	 *	 	First, we try to compute:
	 *			  (~x + 1) + y
	 *			= Tmin + Tmin = 0
	 *		Since x = Tmin and y Tmin, we have:
	 *			x = y
	 * Therefore, we can conclude that (~x + 1) + y >= 0 and x <= y are
	 * equivalent when x = Tmin. */
	sum = (~x + 1) + y;
	sign = sum >> 31;
	is_class3 = sign_x & sign_y & !sign; // result of ! is always 1 or 0


	return is_class1 | is_class2 | is_class3;
}




//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	/*	There are 2 situations concerning !x:
	 *	1. result is 0 if x is not 0
	 *	2. result is 1 if x is 0
	 * And there are 2 sub-situations in the first situation shown above:
	 * 	1.1 result is 0 if x is positive
	 * 	1.2 result is 0 if x is negative
	 *
	 *	We know that Tmax and Tmin are two special values, and here
	 * are some facts about them:
	 *                    x                  result      sign bit of result
	 *	Tmax + x:     0                   Tmax               0
	 *	            positive             negative            1
	 *	         negative(except Tmin)  non-negative         0
	 *	              Tmin                 -1                1
	 *
	 *	Tmin + x:     0                   Tmin               1
	 *	           positive              negative            1
	 *	           negative             non-negative         0
	 * 	Thus, x is negative if and only if the sign bit of (Tmin + x)
	 * is 0; x is positive or Tmin if and only if the sign bit of (Tmax +
	 * x) is 1. */
	int Tmin, Tmax;
	int Tmin_plus_x, Tmax_plus_x;
	int Tmin_plus_x_sign, Tmax_plus_x_sign;


	Tmin = 1 << 31;
	Tmax = ~Tmin;


	Tmin_plus_x = Tmin + x;
	Tmax_plus_x = Tmax + x;


	Tmin_plus_x_sign = (Tmin_plus_x >> 31) & 1;
	Tmax_plus_x_sign = (Tmax_plus_x >> 31) & 1;


	/* least-significant-bit(not-negative & not(positive-or-Tmin)) */
	return (Tmin_plus_x_sign & ~Tmax_plus_x_sign) & 1;
}




/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
	/*	Any two's complement number can be represented in binary as:
	 *	X_sign, X_sign, ... , X_sign, X_k, X_k-1, ... , X_1, X_0.
	 * We can call the number of X_signs on the left-most positions "Number
	 * of consecutively equal bits from most-significant bit", abbreviated
	 * as NCEBMSB. And the function howManyBits is about computing:
	 * 	howManyBits(x) = 32 - (NCEBMSB(x) - 1)
	 *
	 *	We konw for a fact that the computation of:
	 *	mask = (x << n) >> n
	 * will have the result in binary representation as:
	 * 	X_32-n-1, X_32-n-1, ... , X_32-n-1, X_32-n-2, ... , X_1, X_0.
	 * Obviously, NCEBMSB(mask) > n.
	 * 	Since expression !(mask ^ x) actually means "mask equals x",
	 * it compute the boolean expression: NCEBMSB(x) > n.
	 *
	 * 	For reducing steps in implementing function howManyBits, we
	 * can use binary search method. In howManyBits, we'll try to compute
	 * the expression !(((x << n) >> n) ^ x) many times. First use n1 = 16,
	 * then use n2 = n1 + 8 or - 8, and so on, until n5 = n4 + 1 or - 1.*/
	int n;
	int more_than_n; // more_than_n should only has 0 or 1 as its value
	int mask;


	n = 16;
	more_than_n = !(((x << n) >> n) ^ x);


	/*	There are 2 situations:
	 *	1. when more_than_n = 0, the expression can be simplify into
	 * n = n - 8.
	 *	2. when more_than_n = 1, the expression can be simplify into
	 * n = n + 8. */
	mask = more_than_n + ~0; // more_than_n - 1
	n = n + (8 & ~mask) + ((~8 + 1) & mask);

	more_than_n = !(((x << n) >> n) ^ x);


	/* n = n + 4 or n = n - 4 */
	mask = more_than_n + ~0; // more_than_n - 1
	n = n + (4 & ~mask) + ((~4 + 1) & mask);

	more_than_n = !(((x << n) >> n) ^ x);


	/* n = n + 2 or n = n - 2 */
	mask = more_than_n + ~0; // more_than_n - 1
	n = n + (2 & ~mask) + ((~2 + 1) & mask);

	more_than_n = !(((x << n) >> n) ^ x);


	/* n = n + 1 or n = n - 1*/
	mask = more_than_n + ~0; // more_than_n - 1
	n = n + (1 & ~mask) + ((~1 + 1) & mask);

	more_than_n = !(((x << n) >> n) ^ x);


	/* n = more_than_n ? n + 1 : n */
	n = n + more_than_n;


	/* n = 1, 2, ... , 31, 32
	 * 32 - (n - 1) = 1, 2, ... , 32 */
	return 32 + (~(n + ~0) + 1);
}




//float
/* 
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
	unsigned int mask_s, mask_e, mask_f;
	unsigned int e, f;

	unsigned int first_bit_of_f;

	unsigned int new_e, new_f;
	unsigned int ret;


	mask_e = 0xFF << 23;
	mask_f = 0x7FFFFF;


	e = (uf & mask_e) >> 23;
	f = uf & mask_f;


	mask_s = 1 << 31;
	if (e == 0) { // denormalized values
		first_bit_of_f = f >> 22;
		if (first_bit_of_f == 0) {
			new_f = f << 1; // 2 * f

			ret = (uf & ~mask_f); // clear f field
			ret = ret | new_f; // set f field to new_f

			return ret;
		} else { // first_bit_of_f = 1
			/*	In this situation, we'll have to transform a
			 * denormalized value to a normalized value.
			 *	Since for a normalized value, significand M =
			 * f + 1, and for a denormalized value, M = f, the
			 * transformation of a denormalized value to a normal-
			 * ized value will substitue the 1 on the first bit on
			 * the right of binary point to a 1 on the left of
			 * binary point in significand. In other words, the new
			 * significand will be the old significand times 2. */
			new_f = (f << 1) & mask_f; // delete first_bit_of_f
			new_e = 1; // for a denormalized value, E = 1 - bias

			ret = uf & mask_s; // clear e and f field
			ret = ret | (new_e << 23); // set e field to new_e
			ret = ret | new_f; // set f field to new_f

			return ret;
		}
	} else if (e == 255) { // special values
		/* 2 * inf = inf
		 * 2 * -inf = -inf
		 * floatScale2(NaN) = NaN */
		return uf;
	} else { // normalized values
		if (e == 254) { // result will be too big for a normalized value
			ret = uf & mask_s; // keep only original sign bit
			ret = ret | (255 << 23); // set e field to all 1

			return ret; // return -inf or inf
		} else {
			new_e = e + 1;

			ret = (uf & ~mask_e); // clear e field
			ret = ret | (new_e << 23); // set e field to new_e

			return ret;
		}
	}
}




/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
	unsigned int mask_e, mask_f;
	unsigned int s, e, f;
	int E;

	int i;
	unsigned int bit;
	int Tmin, Tmax; 
	int ret;


	mask_e = 0x7F800000; // 0xFF << 23
	mask_f = 0x7FFFFF;


	s = uf >> 31;
	e = (uf & mask_e) >> 23;
	f = uf & mask_f;


	if (e < 127) {		// denormalized and small normalized values
		return 0;
	} else if (e == 255) {	// special values
		return 0x80000000;
	} else {		// normalized values
		E = e - 127;


		/*	Round toward zero: ignore bits on the right of decimal
		 * point in ret. */
		ret = 1;
		for (i = 22; i >= 0; i--, E--) {
			if (E == 0)
				break;

			bit = (f >> i) & 1; // (0 >> i) & 1 = 0

			if (bit == 0)
				ret = ret * 2;
			else // bit = 1
				ret = ret * 2 + 1;
		}


		Tmin = 0x80000000;
		if (s == 1) {
			ret = -ret; // add to it a sign

			for (; E > 0; E--) {
				if (Tmin - ret > ret) // out-of-range value
					return 0x80000000;

				ret *= 2;
			}
		} else {
			Tmax = ~Tmin;

			for (; E > 0; E--) {
				if (Tmax - ret < ret) // out-of-range value
					return 0x80000000;

				ret *= 2;
			}
		}


		return ret;
	}
}




/* 
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 * 
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while 
 *   Max ops: 30 
 *   Rating: 4
 */
unsigned floatPower2(int x) {
	int i, shift_n;

	unsigned int zero;
	unsigned int inf;

	unsigned int e, f;
	int E;

	unsigned int ret;


	zero = 0; // sign = 0, e = 0, f = 0
	inf = 0x7F800000; // sign = 0, e = 255, f = 0


	/* exponent E ranges from -126 to 127 */
	if (x < -126) {
		E = -126;

		f = 1 << 23;
		for (i = x + 126, shift_n = 0; i < 0; i++, shift_n++) {
			if (shift_n > 23) // result will be too small
				return zero;

			f = f >> 1;
		}
	} else if (x > 127) { // result will be too big
		return inf;
	} else { // normalized values
		E = x;
		f = 0;
	}

	e = E + 127;


	/* 2.0^x > 0 */
	ret = 0;
	ret = ret | f;
	ret = ret | (e << 23);

	return ret;
}
