#include "mylibrary.h"


int sum(int n)  // returns the summation of integers from 1 to given integer argument n
{
	int result = 0;

	for (int ii = 1; ii <= n; ii++) {

		result += ii;

	}
	
	return result;
}

int product_of_even_numbers(int *array, int count) // returns the product of even numbers in the given array with length of count
{
	int product = 1;
	
	for (int ii = 0; ii < count; ii++){

		if (array[ii] % 2 == 0) {
			product *= array[ii];
		}
	}
	return product;
}

int max_of_numbers(int *array, int count) // returns the maximum number in the given array with length of count 
{
	int max = array[0];

	for (int ii = 1; ii < count; ii++) {

		if (array[ii] > max) {
			max = array[ii];
		}

	}

	return max;
}

int reversed_number(int number) // returns the revered digits version of the given integer argument
{
	int reversed = 0;
	int numOfDigits = 0;
	int originalNum = number;

	do {
		number /= 10;
		numOfDigits++;
	}
	while (number != 0);

	for (int ii = 1; ii <= numOfDigits; ii++) {
		reversed += (originalNum % 10)*powerTen(numOfDigits - ii);
		originalNum /= 10;
	}

	return reversed;
}


int powerTen(int power) {  // assitant func for reversed_number func 
			   // returns the given integer argument power of ten
	
	int result = 1; 

	for(int ii = 0; ii < power; ii++) {
		
		result *= 10;	
	}

	return result;
}

char alphabet_index(int index) // returns a letter as uppercase corresponding to the given integer argument order in the english alphabet 
{
	int ASCIInum = index + 65; 
	
	if (index >= 0 && index <=25) {
		return ASCIInum;
	}
	else {
		return ' ';
	}
}
