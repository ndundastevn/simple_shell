#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"
#define MAX_COMMAND_LENGTH 512
#define TOKEN_BUFSIZE 64


/**
 * get_args - Tokenizes a string into an array of arguments
 * @str: The string to tokenize
 *
 * Return: An array of arguments (strings)
 */
char **get_args(char *str)
{
	char **args = NULL, *token = NULL;
	int i = 0, bufsize = TOKEN_BUFSIZE;

	args = malloc(bufsize * sizeof(char *));
	if (!args)
		return (NULL);

	token = strtok(str, " \t\r\n#");
	while (token)
	{
		args[i++] = token;
		if (i >= bufsize)
		{
			bufsize += TOKEN_BUFSIZE;
			args = realloc(args, bufsize * sizeof(char *));
			if (!args)
			return (NULL);
		}
		token = strtok(NULL, " \t\r\n#");
	}
	args[i] = NULL;

	return (args);
}
