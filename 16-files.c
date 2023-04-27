#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

/**
 * main - Entry point for the shell
 * @ac: Number of arguments passed to the shell
 * @av: Array of arguments passed to the shell
 * @env: Environment variables
 *
 * Return: 0 on success
 */
int main_filename(int ac, char **av)
{
	char *buffer = NULL;    /* Buffer to read commands from file */
	size_t bufsize = 0;     /* Size of the buffer */
	ssize_t chars_read;     /* Number of chars read from getline */
	FILE *file;             /* Pointer to the file to read commands from */

	if (ac != 2) /* Check if a file was passed as argument */
	{
		fprintf(stderr, "Usage: simple_shell file\n");
		return (EXIT_FAILURE);
	}

	file = fopen(av[1], "r"); /* Open the file for reading */
	if (!file) /* Check if the file was successfully opened */
	{
		perror("simple_shell"); /* Print error message */
		return (EXIT_FAILURE);
	}

	/* Loop through each line of the file */
	while ((chars_read = getline(&buffer, &bufsize, file)) != -1)
	{
		/* Remove the newline character from the end of the line */
		if (buffer[chars_read - 1] == '\n')
			buffer[chars_read - 1] = '\0';

		/* Parse and execute the command */
		execute_command(parse_command(buffer));
	}

	free(buffer);   /* Free the buffer allocated by getline */
	fclose(file);   /* Close the file */
	return (EXIT_SUCCESS);
}
