/* 
 * CS:APP Data Lab 
 * 
 * Alp Kural 71959
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
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

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

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

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
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function. 
     The max operator count is checked by dlc. Note that '=' is not 
     counted; you may use as many of these as you want without penalty.
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
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* 
 * bitAnd - x&y using only ~ and | 
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {	// from the principle of De Morgan's rule the returned statement becomes logically equilavent with the x & y statement
	return ~((~x) | (~y));
}

/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {	// bitwise exclusive or operation returns false if both bits are the same and true otherwise
	return  !(x ^ y);       // if all corresponding bit values are the same, then the exclusive or will result to 0x00, when combined with logical not operator results 1
				// if not it will result other than 0x00 and when combined with logical not operator results 0
}
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {	// determines whether or not the given integer corresponds ASCII digid numbers

	int var1 = x >> 4; 
	int var2 = x & 0x08;
	int var3 = x & 0x06;
	int bool1 = !(var2 ^ 0x08);	// if 3rd bit is 1 return 1, else return 0
	int bool2 = !(var3); 		// if 1rt and 2nd bits are 0 return 1, else return 0
					// bool1 implies bool2, corresponding logical equivalence (not bool1) or bool2
					
	return (!(var1 ^ 0x03)) & ((!bool1) | bool2);
}
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
	
	// if a variable is positive or 0, the most significant bit is 0
	// if a variable is negative, then, the most significant bit is 1
	// the negation of a positive integer is negative, and the negation of a negative integer is positive
	// whereas, the negation of a zero is zero 

	int negX = ~x + 1;	// to get the negative of the variable
	int msbX = x >> 31;     // returns either 0x00 or 0xffffffff, respectively corresponding to the sign bit value 0 or 1
	int msbNegX = negX >> 31; 
	int var = msbX | msbNegX; // returns 0xffffffff for any non zero function input and 0x00 for zero function input value
	
	return var + 0x01;	// returns 0x00 (0) for any non zero function input as 0xffffffff (-1) overflows when incremented by 0x01
				// returns 0x01 (1) for zero function input value as 0x00 (0) is incremented by 0x01
}
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {	// according to two's complement singed integer representation, the numbers overflow as most significant bit (sign bit) passes thorugh 0 to 1
			// where passes through max integer value to min integer value	
	int var = 0x80;
	return var << 24;
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {	// according to the two's complement negation rule, bits of the arguments are flipped and 0x01 added
	int var = 0x01;
	return (~x) + var;
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {   // determines whether or not x is bigger than y
				// compares the signs of the given integers, if x is positive and y is negative, returns 1
				// if x is negative and y is positive, returns 0
				// if the signs of the x and y are the same, then checks whether or not they are the same number, if so returns 0
				// if the signs of the x and y are the same and they are not the same number, then substracts y from x 
				// if the result is positive, x is bigger then y, returns 1
				// if the result is negative, y is bigger then x, returns 0
	int shiftX = x >> 31;		
	int shiftY = y >> 31;		
	int minusY = ~y + 0x01;		
	int res = x + minusY;			
	int var = (shiftX ^ shiftY);		
	res >>= 31;
	return ((var & (~shiftX)) & 0x01)  | ((!(var ^ 0x00)) & (!(!(x ^ y)) & (!res)));
}
/* 
 * float_abs - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_abs(unsigned uf) {
	
	int bitmask1 = ~(0x80 << 24);	// bitmask to turn of the sign bit; by this way if the input value is negative, it becomes positive
					// if it is positive, then, remains positive and if it is zero remains as zero 
	int var = (0xff << 24) >> 1;    // boundary condition for Not A	Number

	if (uf > var) {      		// if the exponent bits are all ones and fraction bits are not all zeros, returns the uf as it is 
		return uf;              // since the bit representation corresponds to Not a Number 
	}
	else {
		return uf & bitmask1;  // applied bit mask to turn off the sign bit
	}
}
/* 
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
	
	int sign = !(!(uf >> 31));   	                    // to obtain the sign bit
	int exponent = (uf >> 23) & 0xff;  		    // to turn off every bit except the exponent section	    
	int fraction = uf & ~((0xff << 24) >> 1);           // to turn off every bit except the fraction section 

	if ((exponent == 0xff) | ((exponent == 0x00) && (fraction == 0x00))) {        // if the exponent bits are all ones, then the input variable is either +/- infinity or NaN 
		return uf;             						      // if the exponenet and fraction bits are all zeros, then, the input variable is zero and when multiplicated by 2 ...
										      // ... the result still remains as zero 
										      // in this condition the input variable should be returned as it is 
	}
	else if ((exponent == 0x00) && (fraction != 0x00)) {
		return (uf << 1) | (sign << 31);   // fraction is left shifted by and sign bit added at the end
	       				           // corresponding to multiplcation of a denormalized floating point number with 2
	}
	else {
		uf += (0x01 << 23);                // exponent is incremented by 1 corresponding multiplication of a normalized floating point number with 2
		return uf; 
	}
}
