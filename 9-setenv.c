#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

#define BUFFER_SIZE 1024


/**
 * set_env - sets a new environment variable or modifies an existing one
 * @argv: the arguments for the setenv command
 */
void set_env(char **argv)
{
	if (argv[1] == NULL || argv[2] == NULL)
	{
		fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
		return;
	}

	if (setenv(argv[1], argv[2], 1) == -1)
	{
		perror("setenv");
	}
}

/**
 * unset_env - removes an environment variable
 * @argv: the arguments for the unsetenv command
 */
void unset_env(char **argv)
{
	if (argv[1] == NULL)
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return;
	}

	if (unsetenv(argv[1]) == -1)
	{
		perror("unsetenv");
	}
}
