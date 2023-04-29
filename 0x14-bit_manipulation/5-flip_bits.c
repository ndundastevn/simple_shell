#include "main.h"

/**
 * flip_bits - calulates the number of bits to flip to get from one number to another
 * @n: first number
 * @m: second number 
 * Return: number of bits that was needed to flip
 */
unsigned int flip_bits(unsigned long int n, unsigned long int m)
{
	unsigned long int dd = n ^ m;
        int cc = 0;

	while (dd)
	{
		cc++;
		dd &= (dd - 1);
	}

	return (cc);
}
