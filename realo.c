#include "myshell.h"
/**
 * _memset - Fill memory with a constant byte
 * @s: Pointer to the memory area to be filled
 * @b: Value to be set
 * @n: Number of bytes to be set to the value
 *
 * Return: Pointer to the memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int k;

	for (k = 0; k < n; k++)
		s[k] = b;
	return (s);
}

/**
 * ffree - Free a pointer array and all its elements
 * @pp: Pointer to the pointer array
 */
void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - Reallocate a memory block
 * @ptr: Pointer to the previously allocated memory block
 * @old_size: Size in bytes of the previously allocated memory block
 * @new_size: Size in bytes of the new memory block
 *
 * Return: Pointer to the new memory block, NULL if the allocation fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
