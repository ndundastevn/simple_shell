#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

int main(void);
void print_prompt(void);
void print_error(char *command);
char *read_input(void);
char **split_input(char *input);
int execute_command(char **args);

/*
 * get_path Function that searches for the executable path
 * of a given command using the PATH environment variable.
 * Returns a pointer to the path.
 */

char *get_path(char *command)
{
	char *path, *token, *temp;
	char *path_copy = strdup(getenv("PATH"));

	if (path_copy == NULL)
	{
		fprintf(stderr, "Error: allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok(path_copy, ":");
	while (token != NULL)
	{
		temp = malloc(strlen(token) + strlen(command) + 2);
		if (temp == NULL)
		{
			fprintf(stderr, "Error: allocation error\n");
			exit(EXIT_FAILURE);
		}

		sprintf(temp, "%s/%s", token, command);
		if (access(temp, X_OK) == 0)
		{
			path = temp;
			break;
		}

		free(temp);
		token = strtok(NULL, ":");
        }

	free(path_copy);

	return (path);
}
