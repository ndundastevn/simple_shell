#include <stdio.h>
#include <unistd.h>

/**
 * main - Entry point for app
 * Description: cod to print lowercase alphabt
 * Return: 0
*/
int main(void)
{
int cha;
for (cha = 'a'; cha <= 'z'; cha++)
{
if (cha != 'e' && cha != 'q')
{
putchar(cha);
}
else
{
}
}
putchar('\n');
return (0);
}
