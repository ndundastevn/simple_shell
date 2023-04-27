#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shell.h"

#define BUFFER_SIZE 1024

/**
 * read_line - reads a line from stdin
 * Return: the line read from stdin
 */
char *read_line(void)
{
	static char buffer[BUFFER_SIZE];
	static int position = 0;
	int c = 0;

	while (1)
	{
		c = getchar();

		if (c == EOF || c == '\n')
		{
			buffer[position] = '\0';
			position = 0;
			return (buffer);
		}
		else
		{
			buffer[position] = c;
		}

		position++;

		if (position >= BUFFER_SIZE)
		{
			fprintf(stderr, "Error: line too long\n");
			exit(EXIT_FAILURE);
		}
	}
}

/**
 * parse_line - parses a line into arguments
 * @line: the line to parse
 * Return: an array of pointers to arguments
 */
char **parse_line(char *line)
{
	static char *argv[100];
	int argc = 0;

	char *token = strtok(line, " ");

	while (token != NULL)
	{
		argv[argc] = token;
		argc++;
		token = strtok(NULL, " ");
	}

	argv[argc] = NULL;
	return (argv);
}

/**
 * execute - executes a command with arguments
 * @argv: the command to execute and its arguments
 */
void execute(char **argv)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (execvp(argv[0], argv) == -1)
		{
			fprintf(stderr, "Error: command not found\n");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

/**
 * main_exit - the entry point of the program
 * Return: the exit status of the program
 */
int main_exit(void)
{
	char *line;
	char **argv;
	int status;

	do {
		printf("$ ");
		line = read_line();
		argv = parse_line(line);

		if (strcmp(argv[0], "exit") == 0)
		{
			if (argv[1] != NULL)
			{
				status = atoi(argv[1]);
				exit(status);
			}
			else
			{
				exit(EXIT_SUCCESS);
			}
		}
		else if (strcmp(argv[0], "env") == 0)
		{
			char **env = __environ;

			while (*env != NULL)
			{
				printf("%s\n", *env);
				env++;
			}
		}
		else if (argv[0][0] != '\0')
		{
			execute(argv);
		}
	} while (1);

	return (EXIT_SUCCESS);
}
