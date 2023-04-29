#include "main.h"

/**
 * _islower - Entry point
 * Description: checks is a character is lowercase
 * @c: check value receives
 * Return: true or false
 */
int _islower(int c)
{
int i = 'a';

for (i = 'a'; i <= 'z'; i++)
{
/* refer int c*/
if (c == i)
{
return (1);
}
}
return (0);
}
