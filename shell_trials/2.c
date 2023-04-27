#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void print_prompt(void);
char *read_input(void);
char **split_input(char *input);
char *get_path(char *command);
void print_error(void);

/*
 * main - Main function that runs the shell program.
 * Reads user input, splits it into arguments, 
 * and executes the corresponding command.
 * return zero
 */

int main(void)
{
	char *buffer, **args, *path, *command;
	int status;

	while (1)
	{
		print_prompt(); /* function to print the shell prompt */
		buffer = read_input(); /* function to read input from user */
		if (buffer == NULL)
			break;
		args = split_input(buffer); /* function to split the input into arguments */
		free(buffer);
		if (args == NULL)
			continue;
		command = args[0];
		path = get_path(command); /* function to get the PATH environment variable */
		if (path == NULL)
			print_error(); /* function to print error message if command not found */
		else
		{
			pid_t pid = fork(); /* fork to create a child process */

			if (pid == -1)
				perror("Error: ");
			else if (pid == 0)
			{
			if (execve(path, args, NULL) == -1) /* execute the command with execve */
				{
					perror("Error: ");
						exit(EXIT_FAILURE);
				}
			}
			else
			{
				wait(&status); /* wait for child process to complete */
			}
		}
		free(path);
		free(args);
	}
	return (0);
}

/*
 * print_prompt - Function that prints the shell prompt "$ ".
 * return (zero)
 */

void print_prompt(void)
{
	printf("$ "); /* print the shell prompt */
}
/*
 * print-error - Function that prints an error message when
 * the command entered by the user is not found.
 * return (zero)
 */

void print_error(void)
{
	printf("Command not found\n");
}

/*
 * read_inputFunction that reads input from the user.
 * returns a pointer to the input buffer.
 */

char *read_input(void)
{
	size_t bufsize = 0;
	char *buffer = NULL;

	if (getline(&buffer, &bufsize, stdin) == -1)
		return NULL;

	return (buffer);
}

/*
 * split_input - Function that splits a string into an array of tokens
 * using whitespace as the delimiter.
 * Returns a pointer to the array of tokens.
 */

char **split_input(char *input)
{
	char **tokens = malloc(sizeof(char *) * 64);
	char *token;
	int index = 0;

	if (tokens == NULL)
	{
		fprintf(stderr, "Error: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, " \t\n\r\a");
	while (token != NULL)
	{
		tokens[index] = token;
		index++;

		token = strtok(NULL, " \t\n\r\a");
	}
	tokens[index] = NULL;

	return (tokens);
}
