#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "shell.h"

/**
 * change_directory - changes the current directory of the process
 * @path: the directory to change to
 * @oldpwd: the previous directory (before the change)
 * Return: 0 on success, -1 on failure
 */
int change_directory(const char *path, char **oldpwd)
{
	char *cwd = NULL;

	if (path == NULL)
		path = getenv("HOME");

	if (path[0] == '-')
	{
		path = getenv("OLDPWD");
		if (path == NULL)
		{
			dprintf(STDERR_FILENO, "cd: OLDPWD not set\n");
			return (-1);
		}
		printf("%s\n", path);
	}

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (-1);
	}

	if (chdir(path) == -1)
	{
		perror("chdir");
		free(cwd);
		return (-1);
	}

	if (*oldpwd)
		free(*oldpwd);
	*oldpwd = cwd;

	if (setenv("OLDPWD", cwd, 1) == -1)
		perror("setenv");

	if (setenv("PWD", getcwd(NULL, 0), 1) == -1)
		perror("setenv");

	return (0);
}

/**
 * builtin_cd - executes the built-in command cd
 * @argv: the command arguments (argv[0] is "cd")
 * @envp: the environment variables
 * @oldpwd: the previous directory (before the change)
 * Return: 0 on success, 1 on exit, -1 on failure
 */
int builtin_cd(char **argv, char **oldpwd)
{
	int status;

	status = change_directory(argv[1], oldpwd);
	if (status == -1)
		return (-1);

	return (0);
}
