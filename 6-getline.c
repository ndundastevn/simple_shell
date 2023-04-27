#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * custom_getline - reads a line from standard input
 * Return: pointer to the line read, or NULL on failure or EOF
 */
char *custom_getline(void)
{
	static char buffer[BUFFER_SIZE];
	static size_t pos;
	static ssize_t read_bytes;

	char *line = NULL;

	while (1)
	{
		if (pos >= (size_t)read_bytes)
		{
			pos = 0;
			read_bytes = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (read_bytes == 0)
				return (line);
			if (read_bytes == -1)
				return (NULL);
		}

		if (buffer[pos] == '\n')
		{
			line = malloc(pos + 1);
			if (!line)
				return (NULL);

			memcpy(line, buffer, pos);
			line[pos] = '\0';
			pos++;
			return (line);
		}

		pos++;
	}
}
