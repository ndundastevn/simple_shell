#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"
/**
 * handle_logical_operators - handles the && and || operators in command input
 * @args: array of strings containing command and arguments
 * @command_result: result of the previous command execution
 *
 * Return: 0 on success, -1 on failure
 */
int handle_logical_operators(char **args, int command_result)
{
	int i = 0;
	int prev_operator = 0;

	while (args[i] != NULL)
	{
		if (strcmp(args[i], "&&") == 0)
		{
			prev_operator = 1;
			if (command_result != 0)
				return (0);
		}
		else if (strcmp(args[i], "||") == 0)
		{
			prev_operator = 2;
			if (command_result == 0)
				return (0);
		}
		else if (prev_operator == 0)
		{
			if (execute_command(args) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
