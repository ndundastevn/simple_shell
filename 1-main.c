#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stddef.h>

#define MAX_COMMAND_LENGTH 50
#define PROMPT "# "
int main(void);

/**
 * main - Entry point for the Simple Shell
 *
 * Return: Always 0 (Success)
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	pid_t pid = fork(); /* Fork a child process */

	while (1)
	{
		printf("%s", PROMPT);
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n"); /* End of file (Ctrl+D) */
			break;
		} /* Remove trailing newline character */
		command[strcspn(command, "\n")] = '\0';

		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (execlp(command, command, NULL) < 0) /* Child process */
			{
				perror(command); /* Executable not found */
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status; /* Parent process */

			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
