#include "main.h"

/**
 * get_bit - returns the value of a bit at a given index.
 * @n: checking bits
 * @index: the index of bit to  to check 
 *
 * Return: the value of the bit at index or -1 if error occures
 */
int get_bit(unsigned long int n, unsigned int index)
{
	unsigned long int ddd, rrr;

	if (index > (sizeof(unsigned long int) * 8 - 1))
		return (-1);
	ddd = 1 << index;
	rrr = n & ddd;
	if (rrr == ddd)
		return (1);

	return (0);
}
