#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

#define MAX_CMD_LEN 1024
#define MAX_ARGS 64
int execute_command_sep(char *cmd);
int main_sep(void);


/**
 * execute_command_sep - executes a single command
 * @cmd: the command to execute
 *
 * Return: 0 on success, -1 on failure
 */
int execute_command_sep(char *cmd)
{
	pid_t pid;
	char *argv[MAX_ARGS];
	int status;
	/* Tokenize the command into arguments */
	int argc = 0;

	pid = fork();

	/* Split the command by spaces, tabs, and newlines */
	argv[argc++] = strtok(cmd, " \t\n");
	while (argc < MAX_ARGS && (argv[argc] = strtok(NULL, " \t\n")) != NULL)
		argc++;

	if (argc == 0) /* Empty command */
		return (0);

	/* Fork a child process to execute the command */
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	else if (pid == 0) /* Child process */
	{
		if (execvp(argv[0], argv) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else /* Parent process */
	{
		waitpid(pid, &status, 0); /* Wait for child process to complete */
		if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_FAILURE)
			return (-1); /* Child process exited with failure status */
	}

	return (0);
}

/**
 * main_sep - Entry point to the program
 *
 * Return: 0 on success, non-zero on failure
 */
int main_sep(void)
{
	char cmd[MAX_CMD_LEN];
	char *token;

	while (1)
	{
		printf("$ "); /* Prompt for input */
		fflush(stdout); /* Flush stdout to ensure prompt is printed */

		/* Read command from stdin */
		if (fgets(cmd, sizeof(cmd), stdin) == NULL)
		{
			if (feof(stdin)) /* End of file (e.g., Ctrl+D) */
				break;

			perror("fgets");
			exit(EXIT_FAILURE);

		}

		/* Tokenize the input by semicolons */
		token = strtok(cmd, ";");
		while (token != NULL)
		{
			if (execute_command_sep(cmd) == -1) /* Execute the command */
				printf("Command failed: %s\n", token);

			token = strtok(NULL, ";");
		}
	}

	return (0);
}
