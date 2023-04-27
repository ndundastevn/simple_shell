#include <stdio.h>
#include "shell.h"
/**
 * atoi - Converts a string to an integer.
 * @str: The string to be converted.
 *
 * Return: The integer value of the converted string.
 */
int atoi(const char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	/* Skip any leading whitespace */
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
	{
		i++;
	}

	/* Check for a sign character */
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
	{
		sign = 1;
		i++;
	}

	/* Process each digit in the string */
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return (result * sign);
}
