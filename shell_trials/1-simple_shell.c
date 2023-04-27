#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
 * main - Entry point for the Simple Shell
 * @argc: the number of arguments passed to the program
 * @argv: an array of pointers to the arguments
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	while (1) /* Display prompt */
	{
		printf("#cisfun$ ");

		char input[MAX_INPUT]; /* Read user input */

		fgets(input, MAX_INPUT, stdin);

		input[strcspn(input, "\n")] = '\0'; /* Remove newline character */

		pid_t pid = fork(); /* Fork a child process */

		if (pid == -1)
		{
			perror("fork"); /* Fork failed */
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execve(input, argv, NULL) == -1) /* Child process; Execute command */
			{
				perror("execve"); /* Execution failed */
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process; Wait for child process to complete */
			int status;

			wait(&status);

			if (feof(stdin)) /* Check for end of file (Ctrl+D) */
			{
				printf("\n");
				break;
			}
		}
	}

	return (0);
}
