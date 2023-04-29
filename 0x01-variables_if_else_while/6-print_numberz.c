#include <stdio.h>
#include <unistd.h>

/**
 * main - App Entry point
 * Description: code that prints char below 10
 * Return: 0
*/
int main(void)
{
int a;
for (a = 0; a < 10; a++)
{
putchar(a + '0');
}
putchar('\n');
return (0);
}
