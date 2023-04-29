alx-low_level_programming/0x08-recursion/4-pow_recursion.c
@BrightDaniel
BrightDaniel Update 4-pow_recursion.c
 History
 1 contributor
23 lines (20 sloc)  244 Bytes

#include "main.h"
/**
 * _pow_recursion - power
 * @x:int
 * @y:int
 * Return:int
 */

int _pow_recursion(int x, int y)
{
	if (y < 0)
	{
		return (-1);
	}
	else if (y != 0)
		return (x * _pow_recursion(x, y - 1));

	else
	{
		return (1);
	}
}
