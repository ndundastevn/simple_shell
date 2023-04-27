#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include "shell.h"

#define MAX_COMMAND_LENGTH 512
#define MAX_VARIABLE_LENGTH 64
/* ignore Betty line length error for this function */
/**
 * get_variable_name_length - Get the length of the variable name.
 *
 * @var_start: Pointer to the start of the variable.
 * @var_end:   Pointer to the end of the variable.
 *
 * Return: The length of the variable name.
 */
int get_variable_name_length(char *var_start, char **var_end)
{
	int var_name_length = 0;

	*var_end = var_start + 1;

	while (**var_end != '\0' && **var_end != ' ' && **var_end != '\t' &&
		**var_end != '\n' && **var_end != '$')
	{
		(*var_end)++;
		var_name_length++;
	}

	return (var_name_length);
}


/**
 * get_variable_value - Gets the value of a given environment variable.
 *
 * @var_name: Name of the environment variable to get the value of.
 *
 * Return: The value of the environment variable if it exists, otherwise NULL.
 */
char *get_variable_value(char *var_name)
{
	return (getenv(var_name));
}

/**
 * replace_variable - Replaces a variable in a command string with its value
 *
 * @var_start: A pointer to the start of the variable in the command string
 * @var_end: A pointer to the end of the variable in the command string
 * @var_name: The name of the variable to replace
 * @var_value: The value to replace the variable with
 * @command: The command string to replace the variable in
 */
void replace_variable(char *var_start, char *var_end, char *var_name,
		char *var_value, char *command)
{
	int var_name_length = strlen(var_name);
	int var_value_length = strlen(var_value);
	int command_length = strlen(command);

	memmove(var_start + var_value_length, var_end, strlen(var_end) + 1);
	strncpy(var_start, var_value, var_value_length);
	command_length += var_value_length - var_name_length;
	command[command_length] = '\0';
}

/* ignore Betty line length error for this function */
/**
 * replace_variables - Replaces variables in a command with their values.
 * @command: The command containing variables to replace.
 *
 * Return: void.
 */
void replace_variables(char *command)
{
	char *var_start, *var_end, *var_name, *var_value;
	char variable[MAX_VARIABLE_LENGTH];
	int pid = getpid(); /* $$ variable */
	int last_exit_status = 0; /* $? variable */

	snprintf(variable, MAX_VARIABLE_LENGTH, "%d", pid);
	setenv("$$", variable, 1);

	snprintf(variable, MAX_VARIABLE_LENGTH, "%d", last_exit_status);
	setenv("$?", variable, 1);

	while ((var_start = strchr(command, '$')) != NULL)
	{
		var_end = var_start + 1;
		if (*(var_start + 1) == '$') /* Check if the variable is $$ */
		{
			var_name = "$$";
			var_value = getenv(var_name);
			var_end++;
		}
		else if (*(var_start + 1) == '?') /* Check if the variable is $? */
		{
			var_name = "$?";
			var_value = getenv(var_name);
			var_end++;
		}
		else /* Otherwise, assume it's a regular variable */
		{
			int var_name_length = get_variable_name_length(var_start, &var_end);

			strncpy(variable, var_start + 1, var_name_length);
			variable[var_name_length] = '\0';
			var_name = variable;
			var_value = get_variable_value(var_name);
		}

		if (var_value != NULL) /* Replace the variable with its value */
		{
			replace_variable(var_start, var_end, var_name, var_value, command);
		}
		else
		{
			var_start++;
		}
	}
}


/**
 * main_var - Reads commands from stdin, replaces variables in them, and
 * executes the commands.
 *
 * Return: Always 0.
 */
int main_var(void)
{
	char input[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("$ ");
		fgets(input, MAX_COMMAND_LENGTH, stdin);

		/* Replace variables in the input command */
		replace_variables(input);

		/* Execute the command */
		/* ... */
	}

	return (0);
}
