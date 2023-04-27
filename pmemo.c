#include "myshell.h"
/**
 * bfree - Free a pointer and set it to NULL.
 *
 * @ptr: Pointer to the pointer to be freed.
 *
 * Return: 1 if the pointer was successfully freed, 0 if the pointer was NULL.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
