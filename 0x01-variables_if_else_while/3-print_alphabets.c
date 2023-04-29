#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point for the program
 * Description: prints alphabet in lowercase then uppercase
 * Return: 0
*/
int main(void)
{
int cha;
for (cha = 'a'; cha <= 'z'; cha++)
{
putchar(cha);
}
for (cha = 'A'; cha <= 'Z'; cha++)
{
putchar(cha);
}
putchar('\n');
return (0);
}
