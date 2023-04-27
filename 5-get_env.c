#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 50
#define PROMPT "# "

char *read_command(void);
char **parse_command(char *command);
void print_env(void);
int get_env(void);

/**
 * read_command - Read a command from stdin.
 *
 * Return: A pointer to the string containing the command, or NULL if
 *         end of file (Ctrl+D) was encountered.
 */
char *read_command(void)
{
	char *command = malloc(MAX_COMMAND_LENGTH);

	if (command == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
		/* End of file (Ctrl+D) */
		free(command);
		command = NULL;
	}
	else
	{
		/* Remove trailing newline character */
		command[strcspn(command, "\n")] = '\0';
	}

	return (command);
}

/**
 * parse_command - function that splits a string into an array of strings
 * @command: input command to be parsed
 * Return: array of strings
 */

char **parse_command(char *command)
{
	char **args = malloc(2 * sizeof(char *));

	if (args == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	args[0] = strdup(command);
	args[1] = NULL;

	return (args);
}


/**
 * print_env - prints the environment variables
 *
 * Return: Always 0.
 */
void print_env(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

/**
 * get_env - Main function to read commands and execute them
 *
 * Return: Always 0.
 */
int get_env(void)
{
	char *command;
	char **args;

	while (1)
	{
		printf("# ");
		fflush(stdout);

		command = read_command();
		if (command == NULL)
		{
			break;
		}

		args = parse_command(command);

		if (strcmp(args[0], "env") == 0)
		{
			print_env();
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			free(command);
			free(args);
			return (0);
		}
		else
		{
			execute_command(args);
		}

		free(command);
		free(args);
	}

	return (0);
}

