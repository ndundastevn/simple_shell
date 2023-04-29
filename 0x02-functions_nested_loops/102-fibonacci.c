#include <stdio.h>

/**
 * main - Prints the first 52 fibonacci numbers
 * Return: 0
*/
int main(void)
{
	int m = 0;
	long n = 1, k = 2;

	while (m < 50)
	{
		if (m == 0)
			printf("%ld", n);
		else if (m == 1)
			printf(", %ld", k);
		else
		{
			k += n;
			n = k - n;
			printf(", %ld", k);
		}

		++m;
	}

	printf("\n");
	return (0);
}
