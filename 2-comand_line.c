#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * command_line - a simple UNIX command line interpreter
 * @argv: declared as a parameter in the main function
 *
 * Return: Always 0.
 */
int command_line(char **argv)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	pid_t pid;

	pid = fork();

	while (1)
	{
		printf("$ "); /* prompt */
		read = getline(&line, &len, stdin); /* read input */

		if (read == -1) /* handle end of file */
		{
			putchar('\n');
			break;
		}

		line[read - 1] = '\0'; /* remove newline character from input */

		if (pid == -1) /* fork a new process to execute the command */
		{
			perror("fork");
				continue;
		} else if (pid == 0)
		{
		if (execvp(line, argv) == -1) /* child process , execute the command */
		{
			perror(line);
			exit(EXIT_FAILURE);
		}
	} else
		{
			int status; /* parent process; wait for the child to complete */

			waitpid(pid, &status, 0);
		}
	}
		free(line); /* free buffer memory */

	return (0);
}
