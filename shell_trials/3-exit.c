#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void);
void print_prompt(void);
void print_error(char *command);
char *read_input(void);
char **split_input(char *input);
int execute_command(char **args);
char *get_path(char *command);

/**
 * execute_command - Executes a command.
 * @args: An array of argument strings.
 *
 * Description: This function implements the exit built-in command
 *              that exits the shell with a status code of 0.
 *
 * Return: Always returns 0.
 */

int execute_command(char **args)
{
	char *command = args[0];
	char *path = get_path(command);

	if (path == NULL)
	{
		print_error(command);
	return 1;
	}
	else if (strcmp(command, "env") == 0) /* check for the 'env' command */
	{
		char **env = environ;
		while (*env != NULL)
		{
			printf("%s\n", *env);
			env++;
		}
		return 0;
	}
	else
	{
		pid_t pid = fork();
		if (pid == -1)
			perror("Error: ");
		else if (pid == 0)
		{
			if (execve(path, args, NULL) == -1)
			{
				perror("Error: ");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(NULL);
		}
		free(path);
		return 0;
	}
}
